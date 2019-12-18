#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netif {TYPE_1__* nif_devdata; } ;
struct iodesc {struct netif* io_netif; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ (* Transmit ) (TYPE_1__*,int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* GetStatus ) (TYPE_1__*,int /*<<< orphan*/ *,void**) ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_1__ EFI_SIMPLE_NETWORK ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static ssize_t
efinet_put(struct iodesc *desc, void *pkt, size_t len)
{
	struct netif *nif = desc->io_netif;
	EFI_SIMPLE_NETWORK *net;
	EFI_STATUS status;
	void *buf;

	net = nif->nif_devdata;
	if (net == NULL)
		return (-1);

	status = net->Transmit(net, 0, len, pkt, NULL, NULL, NULL);
	if (status != EFI_SUCCESS)
		return (-1);

	/* Wait for the buffer to be transmitted */
	do {
		buf = NULL;	/* XXX Is this needed? */
		status = net->GetStatus(net, NULL, &buf);
		/*
		 * XXX EFI1.1 and the E1000 card returns a different 
		 * address than we gave.  Sigh.
		 */
	} while (status == EFI_SUCCESS && buf == NULL);

	/* XXX How do we deal with status != EFI_SUCCESS now? */
	return ((status == EFI_SUCCESS) ? len : -1);
}