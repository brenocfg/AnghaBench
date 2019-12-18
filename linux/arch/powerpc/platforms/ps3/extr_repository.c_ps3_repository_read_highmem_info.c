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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int ps3_repository_read_highmem_base (unsigned int,scalar_t__*) ; 
 int ps3_repository_read_highmem_size (unsigned int,scalar_t__*) ; 

int ps3_repository_read_highmem_info(unsigned int region_index,
	u64 *highmem_base, u64 *highmem_size)
{
	int result;

	*highmem_base = 0;
	result = ps3_repository_read_highmem_base(region_index, highmem_base);
	return result ? result
		: ps3_repository_read_highmem_size(region_index, highmem_size);
}