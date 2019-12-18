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
struct socket {int dummy; } ;
struct sockaddr_hci {int hci_len; int /*<<< orphan*/  hci_node; int /*<<< orphan*/  hci_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  TYPE_2__* ng_btsocket_hci_raw_pcb_p ;
struct TYPE_4__ {int /*<<< orphan*/  hci_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  pcb_mtx; TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct sockaddr_hci*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_hci_raw_node ; 
 TYPE_2__* so2hci_raw_pcb (struct socket*) ; 
 struct sockaddr* sodupsockaddr (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ng_btsocket_hci_raw_sockaddr(struct socket *so, struct sockaddr **nam)
{
	ng_btsocket_hci_raw_pcb_p	pcb = so2hci_raw_pcb(so);
	struct sockaddr_hci		sa;

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_hci_raw_node == NULL)
		return (EINVAL);

	bzero(&sa, sizeof(sa));
	sa.hci_len = sizeof(sa);
	sa.hci_family = AF_BLUETOOTH;

	mtx_lock(&pcb->pcb_mtx);
	strlcpy(sa.hci_node, pcb->addr.hci_node, sizeof(sa.hci_node));
	mtx_unlock(&pcb->pcb_mtx);

	*nam = sodupsockaddr((struct sockaddr *) &sa, M_NOWAIT);

	return ((*nam == NULL)? ENOMEM : 0);
}