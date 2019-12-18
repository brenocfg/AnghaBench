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
struct pt_section {int dummy; } ;

/* Variables and functions */
 int pte_not_supported ; 

int pt_mk_section(struct pt_section **psection, const char *filename,
		  uint64_t offset, uint64_t size)
{
	(void) psection;
	(void) filename;
	(void) offset;
	(void) size;

	/* This function is not used by our tests. */
	return -pte_not_supported;
}