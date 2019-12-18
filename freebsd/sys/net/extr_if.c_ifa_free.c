#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifaddr {int /*<<< orphan*/  ifa_epoch_ctx; int /*<<< orphan*/  ifa_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_destroy ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
ifa_free(struct ifaddr *ifa)
{

	if (refcount_release(&ifa->ifa_refcnt))
		epoch_call(net_epoch_preempt, &ifa->ifa_epoch_ctx, ifa_destroy);
}