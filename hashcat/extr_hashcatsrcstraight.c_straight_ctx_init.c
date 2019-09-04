#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int example_hashes; int left; int opencl_info; int show; int usage; int version; scalar_t__ attack_mode; scalar_t__ rp_files_cnt; scalar_t__ rp_gen; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_14__ {scalar_t__ wordlist_mode; int hc_workc; char** hc_workv; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_15__ {int enabled; int kernel_rules_cnt; scalar_t__ dicts_cnt; TYPE_4__* kernel_rules_buf; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/ * cmds; } ;
typedef  TYPE_4__ kernel_rule_t ;
struct TYPE_17__ {TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_3__* straight_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 int /*<<< orphan*/  RULE_OP_MANGLE_NOOP ; 
 scalar_t__ WL_MODE_FILE ; 
 scalar_t__ count_dictionaries (char**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_5__*,char*,...) ; 
 int hc_path_is_directory (char*) ; 
 int hc_path_is_file (char*) ; 
 int hc_path_read (char*) ; 
 int /*<<< orphan*/  hcfree (char**) ; 
 scalar_t__ hcmalloc (int) ; 
 int kernel_rules_generate (TYPE_5__*,TYPE_4__**,int*) ; 
 int kernel_rules_load (TYPE_5__*,TYPE_4__**,int*) ; 
 int /*<<< orphan*/  qsort (char**,size_t,int,int /*<<< orphan*/ ) ; 
 char** scan_directory (char*) ; 
 int /*<<< orphan*/  sort_by_stringptr ; 
 int straight_ctx_add_wl (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int straight_ctx_init (hashcat_ctx_t *hashcat_ctx)
{
  straight_ctx_t       *straight_ctx        = hashcat_ctx->straight_ctx;
  user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;
  user_options_t       *user_options        = hashcat_ctx->user_options;

  straight_ctx->enabled = false;

  if (user_options->example_hashes == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->opencl_info    == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  if (user_options->attack_mode == ATTACK_MODE_BF) return 0;

  straight_ctx->enabled = true;

  /**
   * generate NOP rules
   */

  if ((user_options->rp_files_cnt == 0) && (user_options->rp_gen == 0))
  {
    straight_ctx->kernel_rules_buf = (kernel_rule_t *) hcmalloc (sizeof (kernel_rule_t));

    straight_ctx->kernel_rules_buf[0].cmds[0] = RULE_OP_MANGLE_NOOP;

    straight_ctx->kernel_rules_cnt = 1;
  }
  else
  {
    if (user_options->rp_files_cnt)
    {
      const int rc_kernel_load = kernel_rules_load (hashcat_ctx, &straight_ctx->kernel_rules_buf, &straight_ctx->kernel_rules_cnt);

      if (rc_kernel_load == -1) return -1;
    }
    else if (user_options->rp_gen)
    {
      const int rc_kernel_generate = kernel_rules_generate (hashcat_ctx, &straight_ctx->kernel_rules_buf, &straight_ctx->kernel_rules_cnt);

      if (rc_kernel_generate == -1) return -1;
    }
  }

  /**
   * wordlist based work
   */

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    if (user_options_extra->wordlist_mode == WL_MODE_FILE)
    {
      for (int i = 0; i < user_options_extra->hc_workc; i++)
      {
        char *l0_filename = user_options_extra->hc_workv[i];

        // at this point we already verified the path actually exist and is readable

        if (hc_path_is_directory (l0_filename) == true)
        {
          char **dictionary_files;

          dictionary_files = scan_directory (l0_filename);

          if (dictionary_files != NULL)
          {
            qsort (dictionary_files, (size_t) count_dictionaries (dictionary_files), sizeof (char *), sort_by_stringptr);

            for (int d = 0; dictionary_files[d] != NULL; d++)
            {
              char *l1_filename = dictionary_files[d];

              if (hc_path_read (l1_filename) == false)
              {
                event_log_error (hashcat_ctx, "%s: %s", l1_filename, strerror (errno));

                hcfree (dictionary_files);

                return -1;
              }

              if (hc_path_is_file (l1_filename) == true)
              {
                const int rc = straight_ctx_add_wl (hashcat_ctx, l1_filename);

                if (rc == -1)
                {
                  hcfree (dictionary_files);

                  return -1;
                }
              }
            }
          }

          hcfree (dictionary_files);
        }
        else
        {
          const int rc = straight_ctx_add_wl (hashcat_ctx, l0_filename);

          if (rc == -1) return -1;
        }
      }

      if (straight_ctx->dicts_cnt == 0)
      {
        event_log_error (hashcat_ctx, "No usable dictionary file found.");

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {

  }
  else if (user_options->attack_mode == ATTACK_MODE_BF)
  {

  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    for (int i = 0; i < user_options_extra->hc_workc - 1; i++)
    {
      char *l0_filename = user_options_extra->hc_workv[i];

      // at this point we already verified the path actually exist and is readable

      if (hc_path_is_directory (l0_filename) == true)
      {
        char **dictionary_files;

        dictionary_files = scan_directory (l0_filename);

        if (dictionary_files != NULL)
        {
          qsort (dictionary_files, (size_t) count_dictionaries (dictionary_files), sizeof (char *), sort_by_stringptr);

          for (int d = 0; dictionary_files[d] != NULL; d++)
          {
            char *l1_filename = dictionary_files[d];

            if (hc_path_read (l1_filename) == false)
            {
              event_log_error (hashcat_ctx, "%s: %s", l1_filename, strerror (errno));

              hcfree (dictionary_files);

              return -1;
            }

            if (hc_path_is_file (l1_filename) == true)
            {
              const int rc = straight_ctx_add_wl (hashcat_ctx, l1_filename);

              if (rc == -1)
              {
                hcfree (dictionary_files);

                return -1;
              }
            }
          }
        }

        hcfree (dictionary_files);
      }
      else
      {
        const int rc = straight_ctx_add_wl (hashcat_ctx, l0_filename);

        if (rc == -1) return -1;
      }
    }

    if (straight_ctx->dicts_cnt == 0)
    {
      event_log_error (hashcat_ctx, "No usable dictionary file found.");

      return -1;
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    for (int i = 1; i < user_options_extra->hc_workc; i++)
    {
      char *l0_filename = user_options_extra->hc_workv[i];

      // at this point we already verified the path actually exist and is readable

      if (hc_path_is_directory (l0_filename) == true)
      {
        char **dictionary_files;

        dictionary_files = scan_directory (l0_filename);

        if (dictionary_files != NULL)
        {
          qsort (dictionary_files, (size_t) count_dictionaries (dictionary_files), sizeof (char *), sort_by_stringptr);

          for (int d = 0; dictionary_files[d] != NULL; d++)
          {
            char *l1_filename = dictionary_files[d];

            if (hc_path_read (l1_filename) == false)
            {
              event_log_error (hashcat_ctx, "%s: %s", l1_filename, strerror (errno));

              hcfree (dictionary_files);

              return -1;
            }

            if (hc_path_is_file (l1_filename) == true)
            {
              const int rc = straight_ctx_add_wl (hashcat_ctx, l1_filename);

              if (rc == -1)
              {
                hcfree (dictionary_files);

                return -1;
              }
            }
          }
        }

        hcfree (dictionary_files);
      }
      else
      {
        const int rc = straight_ctx_add_wl (hashcat_ctx, l0_filename);

        if (rc == -1) return -1;
      }
    }

    if (straight_ctx->dicts_cnt == 0)
    {
      event_log_error (hashcat_ctx, "No usable dictionary file found.");

      return -1;
    }
  }

  return 0;
}