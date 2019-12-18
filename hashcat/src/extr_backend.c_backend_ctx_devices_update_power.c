#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int quiet; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_10__ {scalar_t__ wordlist_mode; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  scalar_t__ u32 ;
struct TYPE_11__ {scalar_t__ words_base; } ;
typedef  TYPE_3__ status_ctx_t ;
struct TYPE_12__ {int skipped; int skipped_warning; scalar_t__ kernel_power; } ;
typedef  TYPE_4__ hc_device_param_t ;
struct TYPE_13__ {TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_3__* status_ctx; TYPE_6__* backend_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_14__ {int enabled; int backend_devices_cnt; scalar_t__ kernel_power_all; TYPE_4__* devices_param; } ;
typedef  TYPE_6__ backend_ctx_t ;

/* Variables and functions */
 scalar_t__ WL_MODE_FILE ; 
 scalar_t__ WL_MODE_MASK ; 
 int /*<<< orphan*/  event_log_advice (TYPE_5__*,char*) ; 

void backend_ctx_devices_update_power (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t        *backend_ctx         = hashcat_ctx->backend_ctx;
  status_ctx_t         *status_ctx          = hashcat_ctx->status_ctx;
  user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;
  user_options_t       *user_options        = hashcat_ctx->user_options;

  if (backend_ctx->enabled == false) return;

  u32 kernel_power_all = 0;

  for (int backend_devices_idx = 0; backend_devices_idx < backend_ctx->backend_devices_cnt; backend_devices_idx++)
  {
    hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

    if (device_param->skipped == true) continue;

    if (device_param->skipped_warning == true) continue;

    kernel_power_all += device_param->kernel_power;
  }

  backend_ctx->kernel_power_all = kernel_power_all;

  /*
   * Inform user about possible slow speeds
   */

  if ((user_options_extra->wordlist_mode == WL_MODE_FILE) || (user_options_extra->wordlist_mode == WL_MODE_MASK))
  {
    if (status_ctx->words_base < kernel_power_all)
    {
      if (user_options->quiet == false)
      {
        event_log_advice (hashcat_ctx, "The wordlist or mask that you are using is too small.");
        event_log_advice (hashcat_ctx, "This means that hashcat cannot use the full parallel power of your device(s).");
        event_log_advice (hashcat_ctx, "Unless you supply more work, your cracking speed will drop.");
        event_log_advice (hashcat_ctx, "For tips on supplying more work, see: https://hashcat.net/faq/morework");
        event_log_advice (hashcat_ctx, NULL);
      }
    }
  }
}