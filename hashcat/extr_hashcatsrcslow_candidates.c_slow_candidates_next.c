#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ attack_mode; int /*<<< orphan*/  rule_buf_r; int /*<<< orphan*/  rule_buf_l; } ;
typedef  TYPE_2__ user_options_t ;
struct TYPE_19__ {scalar_t__ rule_len_r; scalar_t__ rule_len_l; } ;
typedef  TYPE_3__ user_options_extra_t ;
typedef  scalar_t__ u32 ;
struct TYPE_20__ {int kernel_rules_cnt; TYPE_1__* kernel_rules_buf; } ;
typedef  TYPE_4__ straight_ctx_t ;
typedef  int /*<<< orphan*/  rule_buf_out ;
struct TYPE_21__ {int /*<<< orphan*/  css_cnt; int /*<<< orphan*/  markov_css_buf; int /*<<< orphan*/  root_css_buf; } ;
typedef  TYPE_5__ mask_ctx_t ;
struct TYPE_22__ {int opti_type; } ;
typedef  TYPE_6__ hashconfig_t ;
struct TYPE_23__ {TYPE_3__* user_options_extra; TYPE_2__* user_options; TYPE_4__* straight_ctx; TYPE_5__* mask_ctx; TYPE_11__* combinator_ctx; TYPE_6__* hashconfig; } ;
typedef  TYPE_7__ hashcat_ctx_t ;
struct TYPE_24__ {int pos; char* base_buf; scalar_t__ base_len; char* out_buf; scalar_t__ out_len; size_t rule_pos; size_t rule_pos_prev; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_8__ extra_info_straight_t ;
struct TYPE_25__ {scalar_t__ out_buf; int /*<<< orphan*/  pos; } ;
typedef  TYPE_9__ extra_info_mask_t ;
struct TYPE_15__ {int pos; char* base_buf; scalar_t__ base_len; char* out_buf; scalar_t__ out_len; char* scratch_buf; int comb_pos_prev; int comb_pos; int /*<<< orphan*/ * combs_fp; int /*<<< orphan*/ * base_fp; } ;
typedef  TYPE_10__ extra_info_combi_t ;
struct TYPE_16__ {int combs_cnt; } ;
typedef  TYPE_11__ combinator_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/  cmds; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ const ATTACK_MODE_BF ; 
 scalar_t__ const ATTACK_MODE_COMBI ; 
 scalar_t__ const ATTACK_MODE_STRAIGHT ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int RP_PASSWORD_SIZE ; 
 int _old_apply_rule (int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int apply_rules (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int apply_rules_optimized (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ convert_from_hex (TYPE_7__*,char*,scalar_t__) ; 
 scalar_t__ fgetl (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_next_word (TYPE_7__*,int /*<<< orphan*/ *,char**,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ run_rule_engine (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void slow_candidates_next (hashcat_ctx_t *hashcat_ctx, void *extra_info)
{
  hashconfig_t         *hashconfig         = hashcat_ctx->hashconfig;
  combinator_ctx_t     *combinator_ctx     = hashcat_ctx->combinator_ctx;
  mask_ctx_t           *mask_ctx           = hashcat_ctx->mask_ctx;
  straight_ctx_t       *straight_ctx       = hashcat_ctx->straight_ctx;
  user_options_t       *user_options       = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  const u32 attack_mode = user_options->attack_mode;

  if (attack_mode == ATTACK_MODE_STRAIGHT)
  {
    extra_info_straight_t *extra_info_straight = (extra_info_straight_t *) extra_info;

    if ((extra_info_straight->pos % straight_ctx->kernel_rules_cnt) == 0)
    {
      char *line_buf = NULL;
      u32   line_len = 0;

      while (1)
      {
        FILE *fp = extra_info_straight->fp;

        get_next_word (hashcat_ctx, fp, &line_buf, &line_len);

        line_len = (u32) convert_from_hex (hashcat_ctx, line_buf, line_len);

        // post-process rule engine

        char rule_buf_out[RP_PASSWORD_SIZE];

        if (run_rule_engine ((int) user_options_extra->rule_len_l, user_options->rule_buf_l))
        {
          if (line_len >= RP_PASSWORD_SIZE) continue;

          memset (rule_buf_out, 0, sizeof (rule_buf_out));

          const int rule_len_out = _old_apply_rule (user_options->rule_buf_l, (int) user_options_extra->rule_len_l, line_buf, (int) line_len, rule_buf_out);

          if (rule_len_out < 0) continue;

          line_buf = rule_buf_out;
          line_len = (u32) rule_len_out;
        }

        break;
      }

      memcpy (extra_info_straight->base_buf, line_buf, line_len);

      extra_info_straight->base_len = line_len;
    }

    memcpy (extra_info_straight->out_buf, extra_info_straight->base_buf, extra_info_straight->base_len);

    extra_info_straight->out_len = extra_info_straight->base_len;

    memset (extra_info_straight->out_buf + extra_info_straight->base_len, 0, sizeof (extra_info_straight->out_buf) - extra_info_straight->out_len);

    u32 *out_ptr = (u32 *) extra_info_straight->out_buf;

    if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
    {
      extra_info_straight->out_len = apply_rules_optimized (straight_ctx->kernel_rules_buf[extra_info_straight->rule_pos].cmds, &out_ptr[0], &out_ptr[4], extra_info_straight->out_len);
    }
    else
    {
      extra_info_straight->out_len = apply_rules (straight_ctx->kernel_rules_buf[extra_info_straight->rule_pos].cmds, out_ptr, extra_info_straight->out_len);
    }

    extra_info_straight->rule_pos_prev = extra_info_straight->rule_pos;

    extra_info_straight->rule_pos++;

    if (extra_info_straight->rule_pos == straight_ctx->kernel_rules_cnt)
    {
      extra_info_straight->rule_pos = 0;
    }
  }
  else if (attack_mode == ATTACK_MODE_COMBI)
  {
    extra_info_combi_t *extra_info_combi = (extra_info_combi_t *) extra_info;

    FILE *base_fp  = extra_info_combi->base_fp;
    FILE *combs_fp = extra_info_combi->combs_fp;

    if ((extra_info_combi->pos % combinator_ctx->combs_cnt) == 0)
    {
      char *line_buf = NULL;
      u32   line_len = 0;

      while (1)
      {
        get_next_word (hashcat_ctx, base_fp, &line_buf, &line_len);

        line_len = (u32) convert_from_hex (hashcat_ctx, line_buf, line_len);

        // post-process rule engine

        if (run_rule_engine ((int) user_options_extra->rule_len_l, user_options->rule_buf_l))
        {
          if (line_len >= RP_PASSWORD_SIZE) continue;

          char rule_buf_out[RP_PASSWORD_SIZE];

          memset (rule_buf_out, 0, sizeof (rule_buf_out));

          const int rule_len_out = _old_apply_rule (user_options->rule_buf_l, (int) user_options_extra->rule_len_l, line_buf, (int) line_len, rule_buf_out);

          if (rule_len_out < 0) continue;
        }

        break;
      }

      memcpy (extra_info_combi->base_buf, line_buf, line_len);

      extra_info_combi->base_len = line_len;

      rewind (combs_fp);
    }

    memcpy (extra_info_combi->out_buf, extra_info_combi->base_buf, extra_info_combi->base_len);

    extra_info_combi->out_len = extra_info_combi->base_len;

    char *line_buf = extra_info_combi->scratch_buf;
    u32   line_len = 0;

    while (1)
    {
      line_len = (u32) fgetl (combs_fp, line_buf);

      // post-process rule engine

      if (run_rule_engine ((int) user_options_extra->rule_len_r, user_options->rule_buf_r))
      {
        if (line_len >= RP_PASSWORD_SIZE) continue;

        char rule_buf_out[RP_PASSWORD_SIZE];

        memset (rule_buf_out, 0, sizeof (rule_buf_out));

        const int rule_len_out = _old_apply_rule (user_options->rule_buf_r, (int) user_options_extra->rule_len_r, line_buf, (int) line_len, rule_buf_out);

        if (rule_len_out < 0) continue;
      }

      break;
    }

    memcpy (extra_info_combi->out_buf + extra_info_combi->out_len, line_buf, line_len);

    extra_info_combi->out_len += line_len;

    memset (extra_info_combi->out_buf + extra_info_combi->out_len, 0, sizeof (extra_info_combi->out_buf) - extra_info_combi->out_len);

    extra_info_combi->comb_pos_prev = extra_info_combi->comb_pos;

    extra_info_combi->comb_pos++;

    if (extra_info_combi->comb_pos == combinator_ctx->combs_cnt)
    {
      extra_info_combi->comb_pos = 0;
    }
  }
  else if (attack_mode == ATTACK_MODE_BF)
  {
    extra_info_mask_t *extra_info_mask = (extra_info_mask_t *) extra_info;

    sp_exec (extra_info_mask->pos, (char *) extra_info_mask->out_buf, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, 0, mask_ctx->css_cnt);
  }
}