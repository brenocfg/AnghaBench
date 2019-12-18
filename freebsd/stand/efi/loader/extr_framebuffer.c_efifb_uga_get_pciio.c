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
typedef  int UINTN ;
struct TYPE_2__ {scalar_t__ (* LocateHandle ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_PCI_IO_PROTOCOL ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int /*<<< orphan*/  ByProtocol ; 
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pciio_guid ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uga_guid ; 

__attribute__((used)) static EFI_PCI_IO_PROTOCOL *
efifb_uga_get_pciio(void)
{
	EFI_PCI_IO_PROTOCOL *pciio;
	EFI_HANDLE *buf, *hp;
	EFI_STATUS status;
	UINTN bufsz;

	/* Get all handles that support the UGA protocol. */
	bufsz = 0;
	status = BS->LocateHandle(ByProtocol, &uga_guid, NULL, &bufsz, NULL);
	if (status != EFI_BUFFER_TOO_SMALL)
		return (NULL);
	buf = malloc(bufsz);
	status = BS->LocateHandle(ByProtocol, &uga_guid, NULL, &bufsz, buf);
	if (status != EFI_SUCCESS) {
		free(buf);
		return (NULL);
	}
	bufsz /= sizeof(EFI_HANDLE);

	/* Get the PCI I/O interface of the first handle that supports it. */
	pciio = NULL;
	for (hp = buf; hp < buf + bufsz; hp++) {
		status = OpenProtocolByHandle(*hp, &pciio_guid,
		    (void **)&pciio);
		if (status == EFI_SUCCESS) {
			free(buf);
			return (pciio);
		}
	}
	free(buf);
	return (NULL);
}