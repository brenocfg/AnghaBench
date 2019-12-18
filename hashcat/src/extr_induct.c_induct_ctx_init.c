#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int benchmark; int example_hashes; int keyspace; int left; int backend_info; int show; int stdout_flag; int speed_only; int progress_only; int usage; int version; scalar_t__ attack_mode; int /*<<< orphan*/ * induction_dir; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_8__ {int enabled; char* root_directory; } ;
typedef  TYPE_2__ induct_ctx_t ;
struct TYPE_9__ {TYPE_1__* user_options; TYPE_2__* induct_ctx; TYPE_4__* folder_config; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  session_dir; } ;
typedef  TYPE_4__ folder_config_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTEMPTY ; 
 int INDUCT_DIR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_3__*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hc_mkdir (char*,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hcstrdup (int /*<<< orphan*/ *) ; 
 scalar_t__ rename (char*,char*) ; 
 int rmdir (char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int induct_ctx_init (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  induct_ctx_t    *induct_ctx    = hashcat_ctx->induct_ctx;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  induct_ctx->enabled = false;

  if (user_options->benchmark      == true) return 0;
  if (user_options->example_hashes == true) return 0;
  if (user_options->keyspace       == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->stdout_flag    == true) return 0;
  if (user_options->speed_only     == true) return 0;
  if (user_options->progress_only  == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  if (user_options->attack_mode != ATTACK_MODE_STRAIGHT) return 0;

  induct_ctx->enabled = true;

  if (user_options->induction_dir == NULL)
  {
    char *root_directory;

    hc_asprintf (&root_directory, "%s/%s.%s", folder_config->session_dir, user_options->session, INDUCT_DIR);

    if (rmdir (root_directory) == -1)
    {
      if (errno == ENOENT)
      {
        // good, we can ignore
      }
      else if (errno == ENOTEMPTY)
      {
        char *root_directory_mv;

        hc_asprintf (&root_directory_mv, "%s/%s.induct.%d", folder_config->session_dir, user_options->session, (int) time (NULL));

        if (rename (root_directory, root_directory_mv) != 0)
        {
          event_log_error (hashcat_ctx, "Rename directory %s to %s: %s", root_directory, root_directory_mv, strerror (errno));

          return -1;
        }

        hcfree (root_directory_mv);
      }
      else
      {
        event_log_error (hashcat_ctx, "%s: %s", root_directory, strerror (errno));

        return -1;
      }
    }

    if (hc_mkdir (root_directory, 0700) == -1)
    {
      event_log_error (hashcat_ctx, "%s: %s", root_directory, strerror (errno));

      return -1;
    }

    induct_ctx->root_directory = root_directory;
  }
  else
  {
    induct_ctx->root_directory = hcstrdup (user_options->induction_dir);
  }

  return 0;
}