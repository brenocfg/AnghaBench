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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,float,float) ; 

void
print_temp(uint16_t t)
{
	printf("%u K, %2.2f C, %3.2f F\n", t, (float)t - 273.15, (float)t * 9 / 5 - 459.67);
}