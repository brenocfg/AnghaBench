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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ devices_cnt; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_6__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ status_get_exec_msec_dev (TYPE_2__ const*,scalar_t__) ; 

double status_get_exec_msec_all (const hashcat_ctx_t *hashcat_ctx)
{
  const opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  double exec_all_msec = 0;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    exec_all_msec += status_get_exec_msec_dev (hashcat_ctx, device_id);
  }

  return exec_all_msec;
}