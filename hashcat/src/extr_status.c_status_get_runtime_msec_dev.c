#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int skipped; int skipped_warning; double outerloop_msec; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_6__ {TYPE_3__* backend_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_7__ {TYPE_1__* devices_param; } ;
typedef  TYPE_3__ backend_ctx_t ;

/* Variables and functions */

double status_get_runtime_msec_dev (const hashcat_ctx_t *hashcat_ctx, const int backend_devices_idx)
{
  const backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

  if (device_param->skipped == true) return 0;

  if (device_param->skipped_warning == true) return 0;

  return device_param->outerloop_msec;
}