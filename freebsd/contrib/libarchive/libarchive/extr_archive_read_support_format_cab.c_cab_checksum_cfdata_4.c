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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_le32dec (unsigned char const*) ; 

__attribute__((used)) static uint32_t
cab_checksum_cfdata_4(const void *p, size_t bytes, uint32_t seed)
{
	const unsigned char *b;
	unsigned u32num;
	uint32_t sum;

	u32num = (unsigned)bytes / 4;
	sum = seed;
	b = p;
	for (;u32num > 0; --u32num) {
		sum ^= archive_le32dec(b);
		b += 4;
	}
	return (sum);
}