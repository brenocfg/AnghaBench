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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 unsigned int CTR_DLINE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctr_el0 ; 

__attribute__((used)) static unsigned int
get_dcache_line_size(void)
{
	uint64_t ctr;
	unsigned int dcl_size;

	/* Accessible from all security levels */
	ctr = READ_SPECIALREG(ctr_el0);

	/*
	 * Relevant field [19:16] is LOG2
	 * of the number of words in DCache line
	 */
	dcl_size = CTR_DLINE_SIZE(ctr);

	/* Size of word shifted by cache line size */
	return (sizeof(int) << dcl_size);
}