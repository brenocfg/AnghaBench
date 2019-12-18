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
 int CTL_HW ; 
 int HW_PAGESIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  nitems (int*) ; 
 scalar_t__ npagesizes ; 
 int* pagesizes ; 
 int sysctl (int*,int /*<<< orphan*/ ,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
getpagesize(void)
{
	int mib[2], value;
	size_t size;
	static int pagesize;

	if (pagesize != 0)
		return (pagesize);

	if (npagesizes > 0)
		pagesize = pagesizes[0];

	if (pagesize == 0) {
		mib[0] = CTL_HW;
		mib[1] = HW_PAGESIZE;
		size = sizeof(value);
		if (sysctl(mib, nitems(mib), &value, &size, NULL, 0) == -1)
			pagesize = PAGE_SIZE;
		else
			pagesize = value;
	}

	return (pagesize);
}