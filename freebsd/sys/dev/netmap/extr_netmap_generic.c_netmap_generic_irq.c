#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct netmap_adapter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  txirq; int /*<<< orphan*/  rxirq; } ;
struct TYPE_4__ {TYPE_1__ new; } ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_common_irq (struct netmap_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 TYPE_2__ rate_ctx ; 
 scalar_t__ unlikely (int) ; 

void
netmap_generic_irq(struct netmap_adapter *na, u_int q, u_int *work_done)
{
	if (unlikely(!nm_netmap_on(na)))
		return;

	netmap_common_irq(na, q, work_done);
#ifdef RATE_GENERIC
	if (work_done)
		rate_ctx.new.rxirq++;
	else
		rate_ctx.new.txirq++;
#endif  /* RATE_GENERIC */
}