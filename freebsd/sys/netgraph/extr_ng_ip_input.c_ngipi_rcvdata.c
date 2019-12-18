#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_2__ {scalar_t__ td_ng_outbound; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETISR_IP ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  netisr_dispatch (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  netisr_queue (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static int
ngipi_rcvdata(hook_p hook, item_p item)
{
	struct mbuf *m;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);
	if (curthread->td_ng_outbound)
		netisr_queue(NETISR_IP, m);
	else {
		struct epoch_tracker et;

		NET_EPOCH_ENTER(et);
		netisr_dispatch(NETISR_IP, m);
		NET_EPOCH_EXIT(et);
	}
	return 0;
}