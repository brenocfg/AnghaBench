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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
vhd_checksum(void *buf, size_t sz)
{
	uint8_t *p = buf;
	uint32_t sum;
	size_t ofs;

	sum = 0;
	for (ofs = 0; ofs < sz; ofs++)
		sum += p[ofs];
	return (~sum);
}