#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {int backend_devices_cnt; } ;
typedef  TYPE_2__ backend_ctx_t ;

/* Variables and functions */
 scalar_t__ status_get_exec_msec_dev (TYPE_1__ const*,int) ; 

double status_get_exec_msec_all (const hashcat_ctx_t *hashcat_ctx)
{
  const backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  double exec_all_msec = 0;

  for (int backend_devices_idx = 0; backend_devices_idx < backend_ctx->backend_devices_cnt; backend_devices_idx++)
  {
    exec_all_msec += status_get_exec_msec_dev (hashcat_ctx, backend_devices_idx);
  }

  return exec_all_msec;
}