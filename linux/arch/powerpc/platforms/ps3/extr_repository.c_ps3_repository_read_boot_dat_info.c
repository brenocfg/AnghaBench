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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int ps3_repository_read_boot_dat_address (int /*<<< orphan*/ *) ; 
 int ps3_repository_read_boot_dat_size (unsigned int*) ; 

int ps3_repository_read_boot_dat_info(u64 *lpar_addr, unsigned int *size)
{
	int result;

	*size = 0;
	result = ps3_repository_read_boot_dat_address(lpar_addr);
	return result ? result
		: ps3_repository_read_boot_dat_size(size);
}