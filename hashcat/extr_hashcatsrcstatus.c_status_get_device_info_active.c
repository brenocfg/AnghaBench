#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int devices_active; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_5__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */

int status_get_device_info_active (const hashcat_ctx_t *hashcat_ctx)
{
  const opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  return opencl_ctx->devices_active;
}