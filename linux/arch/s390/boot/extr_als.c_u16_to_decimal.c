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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void u16_to_decimal(char *str, u16 val)
{
	int div = 1;

	while (div * 10 <= val)
		div *= 10;
	while (div) {
		*str++ = '0' + val / div;
		val %= div;
		div /= 10;
	}
	*str = '\0';
}