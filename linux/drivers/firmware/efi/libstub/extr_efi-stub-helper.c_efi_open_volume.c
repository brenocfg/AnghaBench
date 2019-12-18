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
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_loaded_image_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_file_io_interface_t ;
typedef  int /*<<< orphan*/  efi_file_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_FILE_SYSTEM_GUID ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  device_handle ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  efi_file_io_interface ; 
 int /*<<< orphan*/  efi_loaded_image ; 
 int /*<<< orphan*/  efi_printk (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ efi_table_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_protocol ; 
 int /*<<< orphan*/  open_volume ; 

__attribute__((used)) static efi_status_t efi_open_volume(efi_system_table_t *sys_table_arg,
				    efi_loaded_image_t *image,
				    efi_file_handle_t **__fh)
{
	efi_file_io_interface_t *io;
	efi_file_handle_t *fh;
	efi_guid_t fs_proto = EFI_FILE_SYSTEM_GUID;
	efi_status_t status;
	void *handle = (void *)(unsigned long)efi_table_attr(efi_loaded_image,
							     device_handle,
							     image);

	status = efi_call_early(handle_protocol, handle,
				&fs_proto, (void **)&io);
	if (status != EFI_SUCCESS) {
		efi_printk(sys_table_arg, "Failed to handle fs_proto\n");
		return status;
	}

	status = efi_call_proto(efi_file_io_interface, open_volume, io, &fh);
	if (status != EFI_SUCCESS)
		efi_printk(sys_table_arg, "Failed to open volume\n");
	else
		*__fh = fh;

	return status;
}