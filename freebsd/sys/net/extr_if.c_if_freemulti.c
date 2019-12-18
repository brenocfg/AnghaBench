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
struct ifmultiaddr {scalar_t__ ifma_refcount; int /*<<< orphan*/  ifma_epoch_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_destroymulti ; 
 int /*<<< orphan*/  net_epoch_preempt ; 

void
if_freemulti(struct ifmultiaddr *ifma)
{
	KASSERT(ifma->ifma_refcount == 0, ("if_freemulti_epoch: refcount %d",
	    ifma->ifma_refcount));

	epoch_call(net_epoch_preempt, &ifma->ifma_epoch_ctx, if_destroymulti);
}