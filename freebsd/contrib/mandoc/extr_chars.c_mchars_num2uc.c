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
 int /*<<< orphan*/  assert (int) ; 
 int mandoc_strntoi (char const*,size_t,int) ; 

int
mchars_num2uc(const char *p, size_t sz)
{
	int	 i;

	i = mandoc_strntoi(p, sz, 16);
	assert(i >= 0 && i <= 0x10FFFF);
	return i;
}