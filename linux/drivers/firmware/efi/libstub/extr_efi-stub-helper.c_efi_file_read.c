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
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned long*,void*) ; 
 int /*<<< orphan*/  efi_file_handle ; 
 int /*<<< orphan*/  read ; 

__attribute__((used)) static efi_status_t efi_file_read(void *handle, unsigned long *size, void *addr)
{
	return efi_call_proto(efi_file_handle, read, handle, size, addr);
}