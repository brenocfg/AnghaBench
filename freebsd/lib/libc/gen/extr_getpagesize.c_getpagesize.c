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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int /*<<< orphan*/  AT_PAGESZ ; 
 int CTL_HW ; 
 int HW_PAGESIZE ; 
 int PAGE_SIZE ; 
 int _elf_aux_info (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
getpagesize(void)
{
	int mib[2];
	static int value;
	size_t size;
	int error;

	if (value != 0)
		return (value);

	error = _elf_aux_info(AT_PAGESZ, &value, sizeof(value));
	if (error == 0 && value != 0)
		return (value);

	mib[0] = CTL_HW;
	mib[1] = HW_PAGESIZE;
	size = sizeof value;
	if (sysctl(mib, nitems(mib), &value, &size, NULL, 0) == -1)
		return (PAGE_SIZE);

	return (value);
}