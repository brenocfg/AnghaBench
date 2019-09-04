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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {TYPE_2__* devices_param; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_6__ {int skipped; int skipped_warning; int /*<<< orphan*/  outerloop_left; } ;
typedef  TYPE_2__ hc_device_param_t ;
struct TYPE_7__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */

u64 status_get_progress_dev (const hashcat_ctx_t *hashcat_ctx, const int device_id)
{
  const opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  hc_device_param_t *device_param = &opencl_ctx->devices_param[device_id];

  if (device_param->skipped == true) return 0;

  if (device_param->skipped_warning == true) return 0;

  return device_param->outerloop_left;
}