#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int benchmark; int example_hashes; int keyspace; int left; int backend_info; int show; int stdout_flag; int speed_only; int progress_only; int usage; int version; int restore_disable; int restore; int /*<<< orphan*/ * restore_file_path; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_13__ {scalar_t__ version; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
typedef  TYPE_2__ restore_data_t ;
struct TYPE_14__ {int enabled; int argc; char** argv; int restore_execute; TYPE_2__* rd; int /*<<< orphan*/  new_restore_file; int /*<<< orphan*/  eff_restore_file; } ;
typedef  TYPE_3__ restore_ctx_t ;
struct TYPE_15__ {TYPE_1__* user_options; TYPE_3__* restore_ctx; TYPE_5__* folder_config; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  session_dir; } ;
typedef  TYPE_5__ folder_config_t ;

/* Variables and functions */
 scalar_t__ RESTORE_VERSION_MIN ; 
 int /*<<< orphan*/  event_log_error (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  hc_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  hcstrdup (int /*<<< orphan*/ *) ; 
 int init_restore (TYPE_4__*) ; 
 int read_restore (TYPE_4__*) ; 
 int user_options_getopt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_options_init (TYPE_4__*) ; 

int restore_ctx_init (hashcat_ctx_t *hashcat_ctx, int argc, char **argv)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  restore_ctx_t   *restore_ctx   = hashcat_ctx->restore_ctx;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  restore_ctx->enabled = false;

  if (user_options->benchmark       == true) return 0;
  if (user_options->example_hashes  == true) return 0;
  if (user_options->keyspace        == true) return 0;
  if (user_options->left            == true) return 0;
  if (user_options->backend_info    == true) return 0;
  if (user_options->show            == true) return 0;
  if (user_options->stdout_flag     == true) return 0;
  if (user_options->speed_only      == true) return 0;
  if (user_options->progress_only   == true) return 0;
  if (user_options->usage           == true) return 0;
  if (user_options->version         == true) return 0;
  if (user_options->restore_disable == true) return 0;

  if (argc ==    0) return 0;
  if (argv == NULL) return 0;

  if (user_options->restore_file_path == NULL)
  {
    hc_asprintf (&restore_ctx->eff_restore_file, "%s/%s.restore",     folder_config->session_dir, user_options->session);
    hc_asprintf (&restore_ctx->new_restore_file, "%s/%s.restore.new", folder_config->session_dir, user_options->session);
  }
  else
  {
    restore_ctx->eff_restore_file = hcstrdup (user_options->restore_file_path);
    hc_asprintf (&restore_ctx->new_restore_file, "%s.new", user_options->restore_file_path);
  }

  restore_ctx->argc = argc;
  restore_ctx->argv = argv;

  if (init_restore (hashcat_ctx) == -1) return -1;

  restore_ctx->enabled = true;

  restore_ctx->restore_execute = false;

  if (user_options->restore == true)
  {
    if (read_restore (hashcat_ctx) == -1) return -1;

    restore_data_t *rd = restore_ctx->rd;

    if (rd->version < RESTORE_VERSION_MIN)
    {
      event_log_error (hashcat_ctx, "Incompatible restore-file version.");

      return -1;
    }

    user_options_init (hashcat_ctx);

    if (user_options_getopt (hashcat_ctx, rd->argc, rd->argv) == -1) return -1;

    restore_ctx->restore_execute = true;
  }

  return 0;
}