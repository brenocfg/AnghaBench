#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ attack_mode; int slow_candidates; } ;
typedef  TYPE_1__ user_options_t ;
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_16__ {int /*<<< orphan*/ * kernel_rules_buf; } ;
typedef  TYPE_2__ straight_ctx_t ;
struct TYPE_17__ {scalar_t__ i; scalar_t__ pw_len; } ;
typedef  TYPE_3__ pw_t ;
struct TYPE_18__ {size_t rule_idx; char* base_buf; size_t base_len; } ;
typedef  TYPE_4__ pw_pre_t ;
struct TYPE_19__ {int gidvid; int il_pos; } ;
typedef  TYPE_5__ plain_t ;
struct TYPE_20__ {int const innerloop_pos; TYPE_4__* pws_base_buf; } ;
typedef  TYPE_6__ hc_device_param_t ;
struct TYPE_21__ {TYPE_1__* user_options; TYPE_2__* straight_ctx; TYPE_8__* debugfile_ctx; } ;
typedef  TYPE_7__ hashcat_ctx_t ;
struct TYPE_22__ {int mode; } ;
typedef  TYPE_8__ debugfile_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 int gidd_to_pw_t (TYPE_7__*,TYPE_6__*,int const,TYPE_3__*) ; 
 int kernel_rule_to_cpu_rule (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,size_t) ; 

int build_debugdata (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, plain_t *plain, u8 *debug_rule_buf, int *debug_rule_len, u8 *debug_plain_ptr, int *debug_plain_len)
{
  const debugfile_ctx_t *debugfile_ctx = hashcat_ctx->debugfile_ctx;
  const straight_ctx_t  *straight_ctx  = hashcat_ctx->straight_ctx;
  const user_options_t  *user_options  = hashcat_ctx->user_options;

  const u64 gidvid = plain->gidvid;
  const u32 il_pos = plain->il_pos;

  if (user_options->attack_mode != ATTACK_MODE_STRAIGHT) return 0;

  const u32 debug_mode = debugfile_ctx->mode;

  if (debug_mode == 0) return 0;

  if (user_options->slow_candidates == true)
  {
    pw_pre_t *pw_base = device_param->pws_base_buf + gidvid;

    // save rule
    if ((debug_mode == 1) || (debug_mode == 3) || (debug_mode == 4))
    {
      const int len = kernel_rule_to_cpu_rule ((char *) debug_rule_buf, &straight_ctx->kernel_rules_buf[pw_base->rule_idx]);

      debug_rule_buf[len] = 0;

      *debug_rule_len = len;
    }

    // save plain
    if ((debug_mode == 2) || (debug_mode == 3) || (debug_mode == 4))
    {
      memcpy (debug_plain_ptr, pw_base->base_buf, pw_base->base_len);

      debug_plain_ptr[pw_base->base_len] = 0;

      *debug_plain_len = pw_base->base_len;
    }
  }
  else
  {
    pw_t pw;

    const int rc = gidd_to_pw_t (hashcat_ctx, device_param, gidvid, &pw);

    if (rc == -1) return -1;

    int plain_len = (int) pw.pw_len;

    const u64 off = device_param->innerloop_pos + il_pos;

    // save rule
    if ((debug_mode == 1) || (debug_mode == 3) || (debug_mode == 4))
    {
      const int len = kernel_rule_to_cpu_rule ((char *) debug_rule_buf, &straight_ctx->kernel_rules_buf[off]);

      debug_rule_buf[len] = 0;

      *debug_rule_len = len;
    }

    // save plain
    if ((debug_mode == 2) || (debug_mode == 3) || (debug_mode == 4))
    {
      memcpy (debug_plain_ptr, (char *) pw.i, (size_t) plain_len);

      debug_plain_ptr[plain_len] = 0;

      *debug_plain_len = plain_len;
    }
  }

  return 0;
}