#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netif {size_t nif_unit; TYPE_2__* nif_driver; } ;
struct TYPE_6__ {scalar_t__ (* OpenProtocol ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* netif_ifs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dif_private; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_SIMPLE_NETWORK ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 TYPE_3__* BS ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (scalar_t__) ; 
 int /*<<< orphan*/  EFI_OPEN_PROTOCOL_EXCLUSIVE ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  IH ; 
 int efi_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_guid ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efinet_probe(struct netif *nif, void *machdep_hint)
{
	EFI_SIMPLE_NETWORK *net;
	EFI_HANDLE h;
	EFI_STATUS status;

	h = nif->nif_driver->netif_ifs[nif->nif_unit].dif_private;
	/*
	 * Open the network device in exclusive mode. Without this
	 * we will be racing with the UEFI network stack. It will
	 * pull packets off the network leading to lost packets.
	 */
	status = BS->OpenProtocol(h, &sn_guid, (void **)&net,
	    IH, NULL, EFI_OPEN_PROTOCOL_EXCLUSIVE);
	if (status != EFI_SUCCESS) {
		printf("Unable to open network interface %d for "
		    "exclusive access: %lu\n", nif->nif_unit,
		    EFI_ERROR_CODE(status));
		return (efi_status_to_errno(status));
	}

	return (0);
}