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
struct ifnet {int /*<<< orphan*/  if_epoch_ctx; int /*<<< orphan*/  if_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_destroy ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 

void
if_rele(struct ifnet *ifp)
{

	if (!refcount_release(&ifp->if_refcount))
		return;
	epoch_call(net_epoch_preempt, &ifp->if_epoch_ctx, if_destroy);
}