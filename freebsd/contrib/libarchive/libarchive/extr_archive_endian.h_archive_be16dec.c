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
typedef  unsigned int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t
archive_be16dec(const void *pp)
{
	unsigned char const *p = (unsigned char const *)pp;

	/* Store into unsigned temporaries before left shifting, to avoid
	promotion to signed int and then left shifting into the sign bit,
	which is undefined behaviour. */
	unsigned int p1 = p[1];
	unsigned int p0 = p[0];

	return ((p0 << 8) | p1);
}