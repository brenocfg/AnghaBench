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
struct TYPE_4__ {scalar_t__ devices_status; int /*<<< orphan*/  timer_paused; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_5__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ STATUS_PAUSED ; 
 scalar_t__ STATUS_RUNNING ; 
 int /*<<< orphan*/  hc_timer_set (int /*<<< orphan*/ *) ; 

int SuspendThreads (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  if (status_ctx->devices_status != STATUS_RUNNING) return -1;

  hc_timer_set (&status_ctx->timer_paused);

  status_ctx->devices_status = STATUS_PAUSED;

  return 0;
}