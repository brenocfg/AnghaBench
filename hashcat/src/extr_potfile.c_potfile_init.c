#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int benchmark; int example_hashes; int keyspace; int backend_info; int stdout_flag; int speed_only; int progress_only; int usage; int version; int potfile_disable; int /*<<< orphan*/ * potfile_path; } ;
typedef  TYPE_2__ user_options_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/ * pfp; } ;
struct TYPE_11__ {int enabled; char* filename; int /*<<< orphan*/ * tmp_buf; int /*<<< orphan*/ * out_buf; TYPE_1__ fp; } ;
typedef  TYPE_3__ potfile_ctx_t ;
struct TYPE_12__ {int potfile_disable; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_13__ {TYPE_2__* user_options; TYPE_3__* potfile_ctx; TYPE_4__* hashconfig; TYPE_6__* folder_config; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  profile_dir; } ;
typedef  TYPE_6__ folder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCBUFSIZ_LARGE ; 
 int /*<<< orphan*/  event_log_warning (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int hc_path_exist (char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 char* hcstrdup (int /*<<< orphan*/ *) ; 

int potfile_init (hashcat_ctx_t *hashcat_ctx)
{
  const folder_config_t *folder_config = hashcat_ctx->folder_config;
  const hashconfig_t    *hashconfig    = hashcat_ctx->hashconfig;
        potfile_ctx_t   *potfile_ctx   = hashcat_ctx->potfile_ctx;
  const user_options_t  *user_options  = hashcat_ctx->user_options;

  potfile_ctx->enabled = false;

  if (user_options->benchmark       == true) return 0;
  if (user_options->example_hashes  == true) return 0;
  if (user_options->keyspace        == true) return 0;
  if (user_options->backend_info    == true) return 0;
  if (user_options->stdout_flag     == true) return 0;
  if (user_options->speed_only      == true) return 0;
  if (user_options->progress_only   == true) return 0;
  if (user_options->usage           == true) return 0;
  if (user_options->version         == true) return 0;
  if (user_options->potfile_disable == true) return 0;

  if (hashconfig->potfile_disable == true) return 0;

  potfile_ctx->enabled = true;

  if (user_options->potfile_path == NULL)
  {
    potfile_ctx->fp.pfp   = NULL;

    hc_asprintf (&potfile_ctx->filename, "%s/hashcat.potfile", folder_config->profile_dir);
  }
  else
  {
    potfile_ctx->filename = hcstrdup (user_options->potfile_path);
    potfile_ctx->fp.pfp   = NULL;
  }

  // starting from here, we should allocate some scratch buffer for later use

  u8 *out_buf = (u8 *) hcmalloc (HCBUFSIZ_LARGE);

  potfile_ctx->out_buf = out_buf;

  // we need two buffers in parallel

  u8 *tmp_buf = (u8 *) hcmalloc (HCBUFSIZ_LARGE);

  potfile_ctx->tmp_buf = tmp_buf;

  // old potfile detection

  if (user_options->potfile_path == NULL)
  {
    char *potfile_old;

    hc_asprintf (&potfile_old, "%s/hashcat.pot", folder_config->profile_dir);

    if (hc_path_exist (potfile_old) == true)
    {
      event_log_warning (hashcat_ctx, "Old potfile detected: %s", potfile_old);
      event_log_warning (hashcat_ctx, "New potfile is: %s ", potfile_ctx->filename);
      event_log_warning (hashcat_ctx, NULL);
    }

    hcfree (potfile_old);
  }

  return 0;
}