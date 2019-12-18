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

__attribute__((used)) static int
bcd2int(int bcd)
{
	int retval = 0;
	int place = 1;

	if (bcd > 0x9999)
		return -1;

	while (bcd) {
		retval += (bcd & 0xf) * place;
		bcd >>= 4;
		place *= 10;
	}
	return retval;
}