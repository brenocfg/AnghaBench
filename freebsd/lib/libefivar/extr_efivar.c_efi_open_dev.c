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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int efi_fd ; 
 int /*<<< orphan*/  efi_guid_tbl_compile () ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efi_open_dev(void)
{

	if (efi_fd == -2)
		efi_fd = open("/dev/efi", O_RDWR);
	if (efi_fd < 0)
		efi_fd = -1;
	else
		efi_guid_tbl_compile();
	return (efi_fd);
}