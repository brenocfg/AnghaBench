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
typedef  int uint8_t ;

/* Variables and functions */

int
acpi_checksum(void *p, size_t length)
{
	uint8_t *bp;
	uint8_t sum;

	bp = p;
	sum = 0;
	while (length--)
		sum += *bp++;

	return (sum);
}