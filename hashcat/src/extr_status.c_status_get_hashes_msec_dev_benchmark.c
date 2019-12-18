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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_5__ {int skipped; int skipped_warning; scalar_t__* speed_msec; scalar_t__* speed_cnt; int /*<<< orphan*/  speed_pos; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_6__ {TYPE_3__* backend_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_7__ {TYPE_1__* devices_param; } ;
typedef  TYPE_3__ backend_ctx_t ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 

double status_get_hashes_msec_dev_benchmark (const hashcat_ctx_t *hashcat_ctx, const int backend_devices_idx)
{
  // this function increases accuracy for benchmark modes

  const backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  u64    speed_cnt  = 0;
  double speed_msec = 0;

  hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

  if ((device_param->skipped == false) && (device_param->skipped_warning == false))
  {
    const u32 speed_pos = MAX (device_param->speed_pos, 1);

    speed_cnt  += device_param->speed_cnt[speed_pos - 1];
    speed_msec += device_param->speed_msec[speed_pos - 1];
  }

  double hashes_dev_msec = 0;

  if (speed_msec > 0)
  {
    hashes_dev_msec = (double) speed_cnt / speed_msec;
  }

  return hashes_dev_msec;
}