#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
typedef  TYPE_1__* ng_btsocket_hci_raw_pcb_p ;
struct TYPE_3__ {int /*<<< orphan*/  pcb_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_hci_raw_node ; 
 TYPE_1__* so2hci_raw_pcb (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 

int
ng_btsocket_hci_raw_disconnect(struct socket *so)
{
	ng_btsocket_hci_raw_pcb_p	 pcb = so2hci_raw_pcb(so);

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_hci_raw_node == NULL)
		return (EINVAL);

	mtx_lock(&pcb->pcb_mtx);
	soisdisconnected(so);
	mtx_unlock(&pcb->pcb_mtx);

	return (0);
}