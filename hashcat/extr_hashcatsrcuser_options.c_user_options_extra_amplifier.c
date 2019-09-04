#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int slow_candidates; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_9__ {scalar_t__ attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  int u64 ;
struct TYPE_10__ {int kernel_rules_cnt; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_11__ {int bfs_cnt; } ;
typedef  TYPE_4__ mask_ctx_t ;
struct TYPE_12__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_3__* straight_ctx; TYPE_4__* mask_ctx; TYPE_6__* combinator_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_13__ {int combs_cnt; } ;
typedef  TYPE_6__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 

u64 user_options_extra_amplifier (hashcat_ctx_t *hashcat_ctx)
{
  const combinator_ctx_t     *combinator_ctx     = hashcat_ctx->combinator_ctx;
  const mask_ctx_t           *mask_ctx           = hashcat_ctx->mask_ctx;
  const straight_ctx_t       *straight_ctx       = hashcat_ctx->straight_ctx;
  const user_options_t       *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  if (user_options->slow_candidates == true)
  {
    return 1;
  }
  else
  {
    if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
    {
      if (straight_ctx->kernel_rules_cnt)
      {
        return straight_ctx->kernel_rules_cnt;
      }
    }
    else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
    {
      if (combinator_ctx->combs_cnt)
      {
        return combinator_ctx->combs_cnt;
      }
    }
    else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
    {
      if (mask_ctx->bfs_cnt)
      {
        return mask_ctx->bfs_cnt;
      }
    }
  }

  return 1;
}