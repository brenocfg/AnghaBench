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
 int HALFLIFE ; 
 unsigned long pow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  y ; 

void calc_runnable_avg_yN_inv(void)
{
	int i;
	unsigned int x;

	/* To silence -Wunused-but-set-variable warnings. */
	printf("static const u32 runnable_avg_yN_inv[] __maybe_unused = {");
	for (i = 0; i < HALFLIFE; i++) {
		x = ((1UL<<32)-1)*pow(y, i);

		if (i % 6 == 0) printf("\n\t");
		printf("0x%8x, ", x);
	}
	printf("\n};\n\n");
}