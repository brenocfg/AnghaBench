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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct setup_data {unsigned long next; } ;
struct pci_setup_rom {int dummy; } ;
struct TYPE_2__ {unsigned long setup_data; } ;
struct boot_params {TYPE_1__ hdr; } ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_pci_io_protocol_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 int /*<<< orphan*/  EFI_LOCATE_BY_PROTOCOL ; 
 int /*<<< orphan*/  EFI_PCI_IO_PROTOCOL_GUID ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,void**,...) ; 
 scalar_t__ efi_is_64bit () ; 
 int /*<<< orphan*/  efi_printk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  handle_protocol ; 
 int /*<<< orphan*/  locate_handle ; 
 scalar_t__ preserve_pci_rom_image (int /*<<< orphan*/ *,struct pci_setup_rom**) ; 
 int /*<<< orphan*/  sys_table ; 

__attribute__((used)) static void setup_efi_pci(struct boot_params *params)
{
	efi_status_t status;
	void **pci_handle = NULL;
	efi_guid_t pci_proto = EFI_PCI_IO_PROTOCOL_GUID;
	unsigned long size = 0;
	unsigned long nr_pci;
	struct setup_data *data;
	int i;

	status = efi_call_early(locate_handle,
				EFI_LOCATE_BY_PROTOCOL,
				&pci_proto, NULL, &size, pci_handle);

	if (status == EFI_BUFFER_TOO_SMALL) {
		status = efi_call_early(allocate_pool,
					EFI_LOADER_DATA,
					size, (void **)&pci_handle);

		if (status != EFI_SUCCESS) {
			efi_printk(sys_table, "Failed to allocate memory for 'pci_handle'\n");
			return;
		}

		status = efi_call_early(locate_handle,
					EFI_LOCATE_BY_PROTOCOL, &pci_proto,
					NULL, &size, pci_handle);
	}

	if (status != EFI_SUCCESS)
		goto free_handle;

	data = (struct setup_data *)(unsigned long)params->hdr.setup_data;

	while (data && data->next)
		data = (struct setup_data *)(unsigned long)data->next;

	nr_pci = size / (efi_is_64bit() ? sizeof(u64) : sizeof(u32));
	for (i = 0; i < nr_pci; i++) {
		efi_pci_io_protocol_t *pci = NULL;
		struct pci_setup_rom *rom;

		status = efi_call_early(handle_protocol,
					efi_is_64bit() ? ((u64 *)pci_handle)[i]
						       : ((u32 *)pci_handle)[i],
					&pci_proto, (void **)&pci);
		if (status != EFI_SUCCESS || !pci)
			continue;

		status = preserve_pci_rom_image(pci, &rom);
		if (status != EFI_SUCCESS)
			continue;

		if (data)
			data->next = (unsigned long)rom;
		else
			params->hdr.setup_data = (unsigned long)rom;

		data = (struct setup_data *)rom;
	}

free_handle:
	efi_call_early(free_pool, pci_handle);
}