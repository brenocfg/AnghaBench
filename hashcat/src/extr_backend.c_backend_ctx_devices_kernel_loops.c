#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int slow_candidates; } ;
typedef  TYPE_2__ user_options_t ;
struct TYPE_17__ {scalar_t__ attack_kern; } ;
typedef  TYPE_3__ user_options_extra_t ;
typedef  int u32 ;
struct TYPE_18__ {scalar_t__ kernel_rules_cnt; } ;
typedef  TYPE_4__ straight_ctx_t ;
struct TYPE_19__ {scalar_t__ bfs_cnt; } ;
typedef  TYPE_5__ mask_ctx_t ;
struct TYPE_20__ {int skipped; int skipped_warning; scalar_t__ kernel_loops_min; scalar_t__ kernel_loops_min_sav; scalar_t__ kernel_loops_max; scalar_t__ kernel_loops_max_sav; } ;
typedef  TYPE_6__ hc_device_param_t ;
struct TYPE_21__ {TYPE_1__* salts_buf; } ;
typedef  TYPE_7__ hashes_t ;
struct TYPE_22__ {scalar_t__ attack_exec; } ;
typedef  TYPE_8__ hashconfig_t ;
struct TYPE_23__ {TYPE_3__* user_options_extra; TYPE_2__* user_options; TYPE_4__* straight_ctx; TYPE_11__* backend_ctx; TYPE_5__* mask_ctx; TYPE_7__* hashes; TYPE_8__* hashconfig; TYPE_10__* combinator_ctx; } ;
typedef  TYPE_9__ hashcat_ctx_t ;
struct TYPE_13__ {scalar_t__ combs_cnt; } ;
typedef  TYPE_10__ combinator_ctx_t ;
struct TYPE_14__ {int enabled; int backend_devices_cnt; TYPE_6__* devices_param; } ;
typedef  TYPE_11__ backend_ctx_t ;
struct TYPE_15__ {int salt_iter; } ;

/* Variables and functions */
 scalar_t__ ATTACK_EXEC_INSIDE_KERNEL ; 
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
 int /*<<< orphan*/  KERNEL_BFS ; 
 int /*<<< orphan*/  KERNEL_COMBS ; 
 int /*<<< orphan*/  KERNEL_RULES ; 
 int MIN (int /*<<< orphan*/ ,int) ; 

void backend_ctx_devices_kernel_loops (hashcat_ctx_t *hashcat_ctx)
{
  combinator_ctx_t     *combinator_ctx      = hashcat_ctx->combinator_ctx;
  hashconfig_t         *hashconfig          = hashcat_ctx->hashconfig;
  hashes_t             *hashes              = hashcat_ctx->hashes;
  mask_ctx_t           *mask_ctx            = hashcat_ctx->mask_ctx;
  backend_ctx_t        *backend_ctx         = hashcat_ctx->backend_ctx;
  straight_ctx_t       *straight_ctx        = hashcat_ctx->straight_ctx;
  user_options_t       *user_options        = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;

  if (backend_ctx->enabled == false) return;

  for (int backend_devices_idx = 0; backend_devices_idx < backend_ctx->backend_devices_cnt; backend_devices_idx++)
  {
    hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

    if (device_param->skipped == true) continue;

    if (device_param->skipped_warning == true) continue;

    device_param->kernel_loops_min = device_param->kernel_loops_min_sav;
    device_param->kernel_loops_max = device_param->kernel_loops_max_sav;

    if (device_param->kernel_loops_min < device_param->kernel_loops_max)
    {
      u32 innerloop_cnt = 0;

      if (hashconfig->attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
      {
        if (user_options->slow_candidates == true)
        {
          innerloop_cnt = 1;
        }
        else
        {
          if      (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)  innerloop_cnt = MIN (KERNEL_RULES, (u32) straight_ctx->kernel_rules_cnt);
          else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)     innerloop_cnt = MIN (KERNEL_COMBS, (u32) combinator_ctx->combs_cnt);
          else if (user_options_extra->attack_kern == ATTACK_KERN_BF)        innerloop_cnt = MIN (KERNEL_BFS,   (u32) mask_ctx->bfs_cnt);
        }
      }
      else
      {
        innerloop_cnt = hashes->salts_buf[0].salt_iter;
      }

      if ((innerloop_cnt >= device_param->kernel_loops_min) &&
          (innerloop_cnt <= device_param->kernel_loops_max))
      {
        device_param->kernel_loops_max = innerloop_cnt;
      }
    }
  }
}