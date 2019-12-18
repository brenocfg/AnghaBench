#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ attack_mode; size_t rp_files_cnt; int /*<<< orphan*/ * rp_files; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_13__ {scalar_t__ wordlist_mode; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  size_t u32 ;
struct TYPE_14__ {size_t dicts_pos; int /*<<< orphan*/  dict; int /*<<< orphan*/ * dicts; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_15__ {scalar_t__ words_cnt; } ;
typedef  TYPE_4__ status_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  mask; } ;
typedef  TYPE_5__ mask_ctx_t ;
typedef  int /*<<< orphan*/  logfile_ctx_t ;
struct TYPE_17__ {size_t induction_dictionaries_pos; int /*<<< orphan*/ * induction_dictionaries; scalar_t__ induction_dictionaries_cnt; } ;
typedef  TYPE_6__ induct_ctx_t ;
struct TYPE_18__ {TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_3__* straight_ctx; TYPE_4__* status_ctx; TYPE_5__* mask_ctx; int /*<<< orphan*/ * logfile_ctx; TYPE_6__* induct_ctx; TYPE_8__* combinator_ctx; } ;
typedef  TYPE_7__ hashcat_ctx_t ;
struct TYPE_19__ {scalar_t__ combs_mode; int /*<<< orphan*/  dict2; int /*<<< orphan*/  dict1; } ;
typedef  TYPE_8__ combinator_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ COMBINATOR_MODE_BASE_LEFT ; 
 scalar_t__ COMBINATOR_MODE_BASE_RIGHT ; 
 scalar_t__ WL_MODE_FILE ; 
 int count_words (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_7__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  logfile_sub_msg (char*) ; 
 int /*<<< orphan*/  logfile_sub_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile_sub_var_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int straight_ctx_update_loop (hashcat_ctx_t *hashcat_ctx)
{
  combinator_ctx_t     *combinator_ctx     = hashcat_ctx->combinator_ctx;
  induct_ctx_t         *induct_ctx         = hashcat_ctx->induct_ctx;
  logfile_ctx_t        *logfile_ctx        = hashcat_ctx->logfile_ctx;
  mask_ctx_t           *mask_ctx           = hashcat_ctx->mask_ctx;
  status_ctx_t         *status_ctx         = hashcat_ctx->status_ctx;
  straight_ctx_t       *straight_ctx       = hashcat_ctx->straight_ctx;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;
  user_options_t       *user_options       = hashcat_ctx->user_options;

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    if (user_options_extra->wordlist_mode == WL_MODE_FILE)
    {
      if (induct_ctx->induction_dictionaries_cnt)
      {
        straight_ctx->dict = induct_ctx->induction_dictionaries[induct_ctx->induction_dictionaries_pos];
      }
      else
      {
        straight_ctx->dict = straight_ctx->dicts[straight_ctx->dicts_pos];
      }

      logfile_sub_string (straight_ctx->dict);

      for (u32 i = 0; i < user_options->rp_files_cnt; i++)
      {
        logfile_sub_var_string ("rulefile", user_options->rp_files[i]);
      }

      HCFILE fp;

      if (hc_fopen (&fp, straight_ctx->dict, "rb") == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", straight_ctx->dict, strerror (errno));

        return -1;
      }

      const int rc = count_words (hashcat_ctx, &fp, straight_ctx->dict, &status_ctx->words_cnt);

      hc_fclose (&fp);

      if (rc == -1)
      {
        event_log_error (hashcat_ctx, "Integer overflow detected in keyspace of wordlist: %s", straight_ctx->dict);

        return -1;
      }

      if (status_ctx->words_cnt == 0)
      {
        logfile_sub_msg ("STOP");

        return 0;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    logfile_sub_string (combinator_ctx->dict1);
    logfile_sub_string (combinator_ctx->dict2);

    if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_LEFT)
    {
      HCFILE fp;

      if (hc_fopen (&fp, combinator_ctx->dict1, "rb") == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", combinator_ctx->dict1, strerror (errno));

        return -1;
      }

      const int rc = count_words (hashcat_ctx, &fp, combinator_ctx->dict1, &status_ctx->words_cnt);

      hc_fclose (&fp);

      if (rc == -1)
      {
        event_log_error (hashcat_ctx, "Integer overflow detected in keyspace of wordlist: %s", combinator_ctx->dict1);

        return -1;
      }
    }
    else if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_RIGHT)
    {
      HCFILE fp;

      if (hc_fopen (&fp, combinator_ctx->dict2, "rb") == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", combinator_ctx->dict2, strerror (errno));

        return -1;
      }

      const int rc = count_words (hashcat_ctx, &fp, combinator_ctx->dict2, &status_ctx->words_cnt);

      hc_fclose (&fp);

      if (rc == -1)
      {
        event_log_error (hashcat_ctx, "Integer overflow detected in keyspace of wordlist: %s", combinator_ctx->dict2);

        return -1;
      }
    }

    if (status_ctx->words_cnt == 0)
    {
      logfile_sub_msg ("STOP");

      return 0;
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    logfile_sub_string (mask_ctx->mask);
  }
  else if ((user_options->attack_mode == ATTACK_MODE_HYBRID1) || (user_options->attack_mode == ATTACK_MODE_HYBRID2))
  {
    if (induct_ctx->induction_dictionaries_cnt)
    {
      straight_ctx->dict = induct_ctx->induction_dictionaries[induct_ctx->induction_dictionaries_pos];
    }
    else
    {
      straight_ctx->dict = straight_ctx->dicts[straight_ctx->dicts_pos];
    }

    logfile_sub_string (straight_ctx->dict);
    logfile_sub_string (mask_ctx->mask);

    HCFILE fp;

    if (hc_fopen (&fp, straight_ctx->dict, "rb") == false)
    {
      event_log_error (hashcat_ctx, "%s: %s", straight_ctx->dict, strerror (errno));

      return -1;
    }

    const int rc = count_words (hashcat_ctx, &fp, straight_ctx->dict, &status_ctx->words_cnt);

    hc_fclose (&fp);

    if (rc == -1)
    {
      event_log_error (hashcat_ctx, "Integer overflow detected in keyspace of wordlist: %s", straight_ctx->dict);

      return -1;
    }

    if (status_ctx->words_cnt == 0)
    {
      logfile_sub_msg ("STOP");

      return 0;
    }
  }

  return 0;
}