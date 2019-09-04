#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {int slow_candidates; scalar_t__ attack_mode; } ;
typedef  TYPE_4__ user_options_t ;
typedef  size_t u8 ;
typedef  size_t u64 ;
typedef  size_t u32 ;
struct TYPE_28__ {TYPE_3__* kernel_rules_buf; } ;
typedef  TYPE_5__ straight_ctx_t ;
struct TYPE_29__ {char* i; size_t pw_len; } ;
typedef  TYPE_6__ pw_t ;
struct TYPE_30__ {size_t gidvid; size_t il_pos; } ;
typedef  TYPE_7__ plain_t ;
struct TYPE_31__ {int /*<<< orphan*/  markov_css_buf; int /*<<< orphan*/  root_css_buf; scalar_t__ css_cnt; } ;
typedef  TYPE_8__ mask_ctx_t ;
struct TYPE_32__ {size_t innerloop_pos; size_t const* kernel_params_mp_l_buf64; size_t* kernel_params_mp_r_buf64; size_t* kernel_params_mp_l_buf32; size_t* kernel_params_mp_r_buf32; size_t* kernel_params_mp_buf64; size_t* kernel_params_mp_buf32; TYPE_1__* combs_buf; } ;
typedef  TYPE_9__ hc_device_param_t ;
struct TYPE_20__ {TYPE_2__* salts_buf; } ;
typedef  TYPE_10__ hashes_t ;
struct TYPE_21__ {int opti_type; int opts_type; scalar_t__ pw_max; } ;
typedef  TYPE_11__ hashconfig_t ;
struct TYPE_22__ {TYPE_4__* user_options; TYPE_5__* straight_ctx; TYPE_8__* mask_ctx; TYPE_10__* hashes; TYPE_11__* hashconfig; TYPE_13__* combinator_ctx; } ;
typedef  TYPE_12__ hashcat_ctx_t ;
struct TYPE_23__ {scalar_t__ combs_mode; } ;
typedef  TYPE_13__ combinator_ctx_t ;
struct TYPE_26__ {int /*<<< orphan*/  cmds; } ;
struct TYPE_25__ {int salt_len; } ;
struct TYPE_24__ {size_t pw_len; scalar_t__ i; } ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ COMBINATOR_MODE_BASE_LEFT ; 
 int MIN (int,int const) ; 
 int OPTI_TYPE_APPENDED_SALT ; 
 int OPTI_TYPE_BRUTE_FORCE ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int OPTI_TYPE_SINGLE_HASH ; 
 int OPTS_TYPE_PT_UTF16BE ; 
 int OPTS_TYPE_PT_UTF16LE ; 
 int apply_rules (int /*<<< orphan*/ ,size_t*,int) ; 
 int apply_rules_optimized (int /*<<< orphan*/ ,size_t*,size_t*,int) ; 
 int gidd_to_pw_t (TYPE_12__*,TYPE_9__*,size_t const,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (size_t*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  sp_exec (size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 

int build_plain (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, plain_t *plain, u32 *plain_buf, int *out_len)
{
  const combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;
  const hashconfig_t     *hashconfig     = hashcat_ctx->hashconfig;
  const hashes_t         *hashes         = hashcat_ctx->hashes;
  const mask_ctx_t       *mask_ctx       = hashcat_ctx->mask_ctx;
  const straight_ctx_t   *straight_ctx   = hashcat_ctx->straight_ctx;
  const user_options_t   *user_options   = hashcat_ctx->user_options;

  const u64 gidvid = plain->gidvid;
  const u32 il_pos = plain->il_pos;

  int plain_len = 0;

  u8 *plain_ptr = (u8 *) plain_buf;

  if (user_options->slow_candidates == true)
  {
    pw_t pw;

    const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

    if (rc == -1) return -1;

    memcpy (plain_buf, pw.i, pw.pw_len);

    plain_len = pw.pw_len;
  }
  else
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      pw_t pw;

      const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

      if (rc == -1) return -1;

      const u64 off = device_param->innerloop_pos + il_pos;

      if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
      {
        for (int i = 0; i < 8; i++)
        {
          plain_buf[i] = pw.i[i];
        }

        plain_len = apply_rules_optimized (straight_ctx->kernel_rules_buf[off].cmds, &plain_buf[0], &plain_buf[4], pw.pw_len);
      }
      else
      {
        for (int i = 0; i < 64; i++)
        {
          plain_buf[i] = pw.i[i];
        }

        plain_len = apply_rules (straight_ctx->kernel_rules_buf[off].cmds, plain_buf, pw.pw_len);
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      pw_t pw;

      const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

      if (rc == -1) return -1;

      for (int i = 0; i < 64; i++)
      {
        plain_buf[i] = pw.i[i];
      }

      plain_len = (int) pw.pw_len;

      char *comb_buf = (char *) device_param->combs_buf[il_pos].i;
      u32   comb_len =          device_param->combs_buf[il_pos].pw_len;

      if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_LEFT)
      {
        memcpy (plain_ptr + plain_len, comb_buf, (size_t) comb_len);
      }
      else
      {
        memmove (plain_ptr + comb_len, plain_ptr, (size_t) plain_len);

        memcpy (plain_ptr, comb_buf, comb_len);
      }

      plain_len += comb_len;
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      u64 l_off = device_param->kernel_params_mp_l_buf64[3] + gidvid;
      u64 r_off = device_param->kernel_params_mp_r_buf64[3] + il_pos;

      u32 l_start = device_param->kernel_params_mp_l_buf32[5];
      u32 r_start = device_param->kernel_params_mp_r_buf32[5];

      u32 l_stop = device_param->kernel_params_mp_l_buf32[4];
      u32 r_stop = device_param->kernel_params_mp_r_buf32[4];

      sp_exec (l_off, (char *) plain_ptr + l_start, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, l_start, l_start + l_stop);
      sp_exec (r_off, (char *) plain_ptr + r_start, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, r_start, r_start + r_stop);

      plain_len = (int) mask_ctx->css_cnt;
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      pw_t pw;

      const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

      if (rc == -1) return -1;

      for (int i = 0; i < 64; i++)
      {
        plain_buf[i] = pw.i[i];
      }

      plain_len = (int) pw.pw_len;

      u64 off = device_param->kernel_params_mp_buf64[3] + il_pos;

      u32 start = 0;
      u32 stop  = device_param->kernel_params_mp_buf32[4];

      sp_exec (off, (char *) plain_ptr + plain_len, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, start, start + stop);

      plain_len += start + stop;
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
      {
        pw_t pw;

        const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

        if (rc == -1) return -1;

        for (int i = 0; i < 64; i++)
        {
          plain_buf[i] = pw.i[i];
        }

        plain_len = (int) pw.pw_len;

        u64 off = device_param->kernel_params_mp_buf64[3] + il_pos;

        u32 start = 0;
        u32 stop  = device_param->kernel_params_mp_buf32[4];

        memmove (plain_ptr + stop, plain_ptr, plain_len);

        sp_exec (off, (char *) plain_ptr, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, start, start + stop);

        plain_len += start + stop;
      }
      else
      {
        pw_t pw;

        const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

        if (rc == -1) return -1;

        u64 off = device_param->kernel_params_mp_buf64[3] + gidvid;

        u32 start = 0;
        u32 stop  = device_param->kernel_params_mp_buf32[4];

        sp_exec (off, (char *) plain_ptr, mask_ctx->root_css_buf, mask_ctx->markov_css_buf, start, start + stop);

        plain_len = stop;

        char *comb_buf = (char *) device_param->combs_buf[il_pos].i;
        u32   comb_len =          device_param->combs_buf[il_pos].pw_len;

        memcpy (plain_ptr + plain_len, comb_buf, comb_len);

        plain_len += comb_len;
      }
    }

    if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (hashconfig->opti_type & OPTI_TYPE_BRUTE_FORCE) // lots of optimizations can happen here
      {
        if (hashconfig->opti_type & OPTI_TYPE_SINGLE_HASH)
        {
          if (hashconfig->opti_type & OPTI_TYPE_APPENDED_SALT)
          {
            plain_len = plain_len - hashes->salts_buf[0].salt_len;
          }
        }

        if (hashconfig->opts_type & OPTS_TYPE_PT_UTF16LE)
        {
          for (int i = 0, j = 0; i < plain_len; i += 2, j += 1)
          {
            plain_ptr[j] = plain_ptr[i];
          }

          plain_len = plain_len / 2;
        }
        else if (hashconfig->opts_type & OPTS_TYPE_PT_UTF16BE)
        {
          for (int i = 1, j = 0; i < plain_len; i += 2, j += 1)
          {
            plain_ptr[j] = plain_ptr[i];
          }

          plain_len = plain_len / 2;
        }
      }
    }
  }

  const int pw_max = (const int) hashconfig->pw_max;

  if (plain_len > pw_max) plain_len = MIN (plain_len, pw_max);

  plain_ptr[plain_len] = 0;

  *out_len = plain_len;

  return 0;
}