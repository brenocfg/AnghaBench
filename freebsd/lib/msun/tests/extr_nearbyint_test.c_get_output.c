#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double* out; } ;

/* Variables and functions */
 TYPE_1__* tests ; 

__attribute__((used)) static float
get_output(int testindex, int rmodeindex, int negative)
{
	double out;

	if (negative) {	/* swap downwards and upwards if input is negative */
		if (rmodeindex == 1)
			rmodeindex = 2;
		else if (rmodeindex == 2)
			rmodeindex = 1;
	}
	if (rmodeindex == 3) /* FE_TOWARDZERO uses the value for downwards */
		rmodeindex = 1;
	out = tests[testindex].out[rmodeindex];
	return (negative ? -out : out);
}