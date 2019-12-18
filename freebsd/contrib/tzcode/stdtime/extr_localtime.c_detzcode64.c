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
typedef  int time_t ;
typedef  int int_fast64_t ;

/* Variables and functions */

__attribute__((used)) static time_t
detzcode64(const char *const codep)
{
	register time_t	result;
	register int	i;

	result = (codep[0] & 0x80) ?  (~(int_fast64_t) 0) : 0;
	for (i = 0; i < 8; ++i)
		result = result * 256 + (codep[i] & 0xff);
	return result;
}