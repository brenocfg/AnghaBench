#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_13__ {int argc; char** argv; char* cwd; } ;
typedef  TYPE_1__ restore_data_t ;
struct TYPE_14__ {int enabled; char* eff_restore_file; TYPE_1__* rd; } ;
typedef  TYPE_2__ restore_ctx_t ;
struct TYPE_15__ {TYPE_4__* folder_config; TYPE_2__* restore_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_16__ {char* install_dir; char* shared_dir; int /*<<< orphan*/  cwd; } ;
typedef  TYPE_4__ folder_config_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ HCBUFSIZ_LARGE ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_3__*,char*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  folder_config_destroy (TYPE_3__*) ; 
 int folder_config_init (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hc_fgets (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int hc_fread (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int hc_path_exist (char*) ; 
 int hc_path_is_directory (char*) ; 
 scalar_t__ hccalloc (int,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 void* hcstrdup (char*) ; 
 int /*<<< orphan*/  pidfile_ctx_destroy (TYPE_3__*) ; 
 int pidfile_ctx_init (TYPE_3__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_restore (hashcat_ctx_t *hashcat_ctx)
{
  restore_ctx_t   *restore_ctx   = hashcat_ctx->restore_ctx;
  folder_config_t *folder_config = hashcat_ctx->folder_config;

  if (restore_ctx->enabled == false) return 0;

  char *eff_restore_file = restore_ctx->eff_restore_file;

  HCFILE fp;

  if (hc_fopen (&fp, eff_restore_file, "rb") == false)
  {
    event_log_error (hashcat_ctx, "Restore file '%s': %s", eff_restore_file, strerror (errno));

    return -1;
  }

  restore_data_t *rd = restore_ctx->rd;

  if (hc_fread (rd, sizeof (restore_data_t), 1, &fp) != 1)
  {
    event_log_error (hashcat_ctx, "Cannot read %s", eff_restore_file);

    hc_fclose (&fp);

    return -1;
  }

  // we only use these 2 checks to avoid "tainted string" warnings

  if (rd->argc < 1)
  {
    event_log_error (hashcat_ctx, "Unusually low number of arguments (argc) within restore file %s", eff_restore_file);

    hc_fclose (&fp);

    return -1;
  }

  if (rd->argc > 250) // some upper bound check is always good (with some dirs/dicts it could be a large string)
  {
    event_log_error (hashcat_ctx, "Unusually high number of arguments (argc) within restore file %s", eff_restore_file);

    hc_fclose (&fp);

    return -1;
  }

  rd->argv = (char **) hccalloc (rd->argc, sizeof (char *));

  char *buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

  for (u32 i = 0; i < rd->argc; i++)
  {
    if (hc_fgets (buf, HCBUFSIZ_LARGE - 1, &fp) == NULL)
    {
      event_log_error (hashcat_ctx, "Cannot read %s", eff_restore_file);

      hc_fclose (&fp);

      hcfree (buf);

      return -1;
    }

    size_t len = strlen (buf);

    if (len) buf[len - 1] = 0;

    rd->argv[i] = hcstrdup (buf);
  }

  hcfree (buf);

  hc_fclose (&fp);

  if (hc_path_exist (rd->cwd) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", rd->cwd, strerror (errno));

    return -1;
  }

  if (hc_path_is_directory (rd->cwd) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", rd->cwd, strerror (errno));

    return -1;
  }

  if (strncmp (rd->cwd, folder_config->cwd, sizeof (rd->cwd)) != 0) // check if we need to change the current working directory
  {
    event_log_warning (hashcat_ctx, "Changing current working directory to '%s'", rd->cwd);
    event_log_warning (hashcat_ctx, NULL);

    if (chdir (rd->cwd))
    {
      event_log_error (hashcat_ctx, "Directory '%s' needed to restore the session was not found.", rd->cwd);

      event_log_warning (hashcat_ctx, "Either create the directory, or update the directory within the .restore file.");
      event_log_warning (hashcat_ctx, "Restore files can be analyzed and modified with analyze_hc_restore.pl:");
      event_log_warning (hashcat_ctx, "    https://github.com/philsmd/analyze_hc_restore");
      event_log_warning (hashcat_ctx, "Directory must contain all files and folders from the original command line.");
      event_log_warning (hashcat_ctx, NULL);

      return -1;
    }

    // if we are here, we also need to update the folder_config and .pid file:

    /**
     * updated folders
     */

    // copy the paths of INSTALL_FOLDER and SHARED_FOLDER from the folder config:

    char *install_folder = hcstrdup (folder_config->install_dir);
    char *shared_folder  = hcstrdup (folder_config->shared_dir);

    folder_config_destroy (hashcat_ctx);

    const int rc_folder_config_init = folder_config_init (hashcat_ctx, install_folder, shared_folder);

    hcfree (install_folder);
    hcfree (shared_folder);

    if (rc_folder_config_init == -1) return -1;

    /**
     * updated pidfile
     */

    pidfile_ctx_destroy (hashcat_ctx);

    if (pidfile_ctx_init (hashcat_ctx) == -1) return -1;
  }

  return 0;
}