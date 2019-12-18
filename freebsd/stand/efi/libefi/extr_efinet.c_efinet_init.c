#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct netif {size_t nif_unit; TYPE_4__* nif_devdata; TYPE_2__* nif_driver; } ;
struct iodesc {int xid; int /*<<< orphan*/  myea; struct netif* io_netif; } ;
typedef  int UINT32 ;
struct TYPE_11__ {int /*<<< orphan*/  Addr; } ;
struct TYPE_13__ {scalar_t__ State; TYPE_3__ CurrentAddress; } ;
struct TYPE_12__ {scalar_t__ (* Start ) (TYPE_4__*) ;scalar_t__ (* Initialize ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* ReceiveFilters ) (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_8__* Mode; } ;
struct TYPE_10__ {TYPE_1__* netif_ifs; } ;
struct TYPE_9__ {scalar_t__ dif_unit; int /*<<< orphan*/  dif_private; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_4__ EFI_SIMPLE_NETWORK ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ERROR_CODE (scalar_t__) ; 
 int EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST ; 
 int EFI_SIMPLE_NETWORK_RECEIVE_UNICAST ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ EfiSimpleNetworkInitialized ; 
 scalar_t__ EfiSimpleNetworkStopped ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_mode (TYPE_8__*) ; 
 int /*<<< orphan*/  efi_env_net_params (struct iodesc*) ; 
 int /*<<< orphan*/  printf (char*,size_t,...) ; 
 int /*<<< orphan*/  sn_guid ; 
 scalar_t__ stub1 (TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efinet_init(struct iodesc *desc, void *machdep_hint)
{
	struct netif *nif = desc->io_netif;
	EFI_SIMPLE_NETWORK *net;
	EFI_HANDLE h;
	EFI_STATUS status;
	UINT32 mask;

	/* Attempt to get netboot params from env */
	efi_env_net_params(desc);

	if (nif->nif_driver->netif_ifs[nif->nif_unit].dif_unit < 0) {
		printf("Invalid network interface %d\n", nif->nif_unit);
		return;
	}

	h = nif->nif_driver->netif_ifs[nif->nif_unit].dif_private;
	status = OpenProtocolByHandle(h, &sn_guid, (void **)&nif->nif_devdata);
	if (status != EFI_SUCCESS) {
		printf("net%d: cannot fetch interface data (status=%lu)\n",
		    nif->nif_unit, EFI_ERROR_CODE(status));
		return;
	}

	net = nif->nif_devdata;
	if (net->Mode->State == EfiSimpleNetworkStopped) {
		status = net->Start(net);
		if (status != EFI_SUCCESS) {
			printf("net%d: cannot start interface (status=%lu)\n",
			    nif->nif_unit, EFI_ERROR_CODE(status));
			return;
		}
	}

	if (net->Mode->State != EfiSimpleNetworkInitialized) {
		status = net->Initialize(net, 0, 0);
		if (status != EFI_SUCCESS) {
			printf("net%d: cannot init. interface (status=%lu)\n",
			    nif->nif_unit, EFI_ERROR_CODE(status));
			return;
		}
	}

	mask = EFI_SIMPLE_NETWORK_RECEIVE_UNICAST |
	    EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST;

	status = net->ReceiveFilters(net, mask, 0, FALSE, 0, NULL);
	if (status != EFI_SUCCESS)
		printf("net%d: cannot set rx. filters (status=%lu)\n",
		    nif->nif_unit, EFI_ERROR_CODE(status));

#ifdef EFINET_DEBUG
	dump_mode(net->Mode);
#endif

	bcopy(net->Mode->CurrentAddress.Addr, desc->myea, 6);
	desc->xid = 1;
}