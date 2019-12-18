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
 int /*<<< orphan*/  __decompress (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_decomp_puts (char*) ; 
 int /*<<< orphan*/  arch_decomp_setup () ; 
 int /*<<< orphan*/  error ; 
 unsigned long free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 unsigned long get_unaligned_le32 (unsigned char*) ; 
 scalar_t__ input_data ; 
 scalar_t__ input_data_end ; 
 unsigned char* output_data ; 
 unsigned long output_ptr ; 

unsigned long decompress_kernel(unsigned long output_start,
		unsigned long free_mem_ptr_p,
		unsigned long free_mem_ptr_end_p)
{
	unsigned char *tmp;

	output_data		= (unsigned char *)output_start;
	free_mem_ptr		= free_mem_ptr_p;
	free_mem_end_ptr	= free_mem_ptr_end_p;

	arch_decomp_setup();

	tmp = (unsigned char *) (((unsigned long)input_data_end) - 4);
	output_ptr = get_unaligned_le32(tmp);

	arch_decomp_puts("Uncompressing Linux...");
	__decompress(input_data, input_data_end - input_data, NULL, NULL,
			output_data, 0, NULL, error);
	arch_decomp_puts(" done, booting the kernel.\n");
	return output_ptr;
}