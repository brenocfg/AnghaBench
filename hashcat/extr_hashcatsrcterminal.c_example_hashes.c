#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hash_mode_chgd; int hash_mode; int /*<<< orphan*/  separator; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/ * st_pass; int /*<<< orphan*/ * st_hash; int /*<<< orphan*/  hash_name; int /*<<< orphan*/  hash_mode; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_10__ {TYPE_2__* hashconfig; TYPE_1__* user_options; int /*<<< orphan*/ * folder_config; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  folder_config_t ;

/* Variables and functions */
 int HCBUFSIZ_LARGE ; 
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 int MODULE_HASH_MODES_MAXIMUM ; 
 int /*<<< orphan*/  event_log_info (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  exec_hexify (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashconfig_destroy (TYPE_3__*) ; 
 int hashconfig_init (TYPE_3__*) ; 
 int hc_path_exist (char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_filename (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ need_hexify (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 

void example_hashes (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  if (user_options->hash_mode_chgd == true)
  {
    const int rc = hashconfig_init (hashcat_ctx);

    if (rc == 0)
    {
      hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

      event_log_info (hashcat_ctx, "MODE: %u", hashconfig->hash_mode);
      event_log_info (hashcat_ctx, "TYPE: %s", hashconfig->hash_name);

      if ((hashconfig->st_hash != NULL) && (hashconfig->st_pass != NULL))
      {
        event_log_info (hashcat_ctx, "HASH: %s", hashconfig->st_hash);

        if (need_hexify ((const u8 *) hashconfig->st_pass, strlen (hashconfig->st_pass), user_options->separator, 0))
        {
          char tmp_buf[HCBUFSIZ_LARGE];

          int tmp_len = 0;

          tmp_buf[tmp_len++] = '$';
          tmp_buf[tmp_len++] = 'H';
          tmp_buf[tmp_len++] = 'E';
          tmp_buf[tmp_len++] = 'X';
          tmp_buf[tmp_len++] = '[';

          exec_hexify ((const u8 *) hashconfig->st_pass, strlen (hashconfig->st_pass), (u8 *) tmp_buf + tmp_len);

          tmp_len += strlen (hashconfig->st_pass) * 2;

          tmp_buf[tmp_len++] = ']';
          tmp_buf[tmp_len++] = 0;

          event_log_info (hashcat_ctx, "PASS: %s", tmp_buf);
        }
        else
        {
          event_log_info (hashcat_ctx, "PASS: %s", hashconfig->st_pass);
        }
      }
      else
      {
        event_log_info (hashcat_ctx, "HASH: not stored");
        event_log_info (hashcat_ctx, "PASS: not stored");
      }

      event_log_info (hashcat_ctx, NULL);
    }

    hashconfig_destroy (hashcat_ctx);
  }
  else
  {
    char *modulefile = (char *) hcmalloc (HCBUFSIZ_TINY);

    for (int i = 0; i < MODULE_HASH_MODES_MAXIMUM; i++)
    {
      user_options->hash_mode = i;

      module_filename (folder_config, i, modulefile, HCBUFSIZ_TINY);

      if (hc_path_exist (modulefile) == false) continue;

      const int rc = hashconfig_init (hashcat_ctx);

      if (rc == 0)
      {
        hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

        event_log_info (hashcat_ctx, "MODE: %u", hashconfig->hash_mode);
        event_log_info (hashcat_ctx, "TYPE: %s", hashconfig->hash_name);

        if ((hashconfig->st_hash != NULL) && (hashconfig->st_pass != NULL))
        {
          event_log_info (hashcat_ctx, "HASH: %s", hashconfig->st_hash);

          if (need_hexify ((const u8 *) hashconfig->st_pass, strlen (hashconfig->st_pass), user_options->separator, 0))
          {
            char tmp_buf[HCBUFSIZ_LARGE];

            int tmp_len = 0;

            tmp_buf[tmp_len++] = '$';
            tmp_buf[tmp_len++] = 'H';
            tmp_buf[tmp_len++] = 'E';
            tmp_buf[tmp_len++] = 'X';
            tmp_buf[tmp_len++] = '[';

            exec_hexify ((const u8 *) hashconfig->st_pass, strlen (hashconfig->st_pass), (u8 *) tmp_buf + tmp_len);

            tmp_len += strlen (hashconfig->st_pass) * 2;

            tmp_buf[tmp_len++] = ']';
            tmp_buf[tmp_len++] = 0;

            event_log_info (hashcat_ctx, "PASS: %s", tmp_buf);
          }
          else
          {
            event_log_info (hashcat_ctx, "PASS: %s", hashconfig->st_pass);
          }
        }
        else
        {
          event_log_info (hashcat_ctx, "HASH: not stored");
          event_log_info (hashcat_ctx, "PASS: not stored");
        }

        event_log_info (hashcat_ctx, NULL);
      }

      hashconfig_destroy (hashcat_ctx);
    }

    hcfree (modulefile);
  }
}