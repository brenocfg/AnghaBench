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
struct TYPE_12__ {int slow_candidates; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_13__ {scalar_t__ attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_14__ {scalar_t__ kernel_rules_cnt; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_15__ {scalar_t__ il_pos; scalar_t__ gidvid; } ;
typedef  TYPE_4__ plain_t ;
struct TYPE_16__ {scalar_t__ bfs_cnt; } ;
typedef  TYPE_5__ mask_ctx_t ;
struct TYPE_17__ {scalar_t__ const innerloop_pos; scalar_t__ words_off; } ;
typedef  TYPE_6__ hc_device_param_t ;
struct TYPE_18__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_3__* straight_ctx; TYPE_5__* mask_ctx; TYPE_8__* combinator_ctx; } ;
typedef  TYPE_7__ hashcat_ctx_t ;
struct TYPE_19__ {scalar_t__ combs_cnt; } ;
typedef  TYPE_8__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
 scalar_t__ ATTACK_MODE_BF ; 

int build_crackpos (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, plain_t *plain, u64 *out_pos)
{
  const combinator_ctx_t      *combinator_ctx     = hashcat_ctx->combinator_ctx;
  const mask_ctx_t            *mask_ctx           = hashcat_ctx->mask_ctx;
  const straight_ctx_t        *straight_ctx       = hashcat_ctx->straight_ctx;
  const user_options_t        *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t  *user_options_extra = hashcat_ctx->user_options_extra;

  const u64 gidvid = plain->gidvid;
  const u32 il_pos = plain->il_pos;

  u64 crackpos = device_param->words_off;

  if (user_options->slow_candidates == true)
  {
    crackpos = gidvid;
  }
  else
  {
    if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
    {
      crackpos += gidvid;
      crackpos *= straight_ctx->kernel_rules_cnt;
      crackpos += device_param->innerloop_pos + il_pos;
    }
    else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
    {
      crackpos += gidvid;
      crackpos *= combinator_ctx->combs_cnt;
      crackpos += device_param->innerloop_pos + il_pos;
    }
    else if (user_options_extra->attack_kern == ATTACK_MODE_BF)
    {
      crackpos += gidvid;
      crackpos *= mask_ctx->bfs_cnt;
      crackpos += device_param->innerloop_pos + il_pos;
    }
  }

  *out_pos = crackpos;

  return 0;
}