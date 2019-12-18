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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  kernel_power_final; } ;
typedef  TYPE_2__ backend_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_SET_KERNEL_POWER_FINAL ; 

__attribute__((used)) static int set_kernel_power_final (hashcat_ctx_t *hashcat_ctx, const u64 kernel_power_final)
{
  EVENT (EVENT_SET_KERNEL_POWER_FINAL);

  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  backend_ctx->kernel_power_final = kernel_power_final;

  return 0;
}