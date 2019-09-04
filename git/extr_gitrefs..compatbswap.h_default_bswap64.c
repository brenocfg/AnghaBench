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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t default_bswap64(uint64_t val)
{
	return (((val & (uint64_t)0x00000000000000ffULL) << 56) |
		((val & (uint64_t)0x000000000000ff00ULL) << 40) |
		((val & (uint64_t)0x0000000000ff0000ULL) << 24) |
		((val & (uint64_t)0x00000000ff000000ULL) <<  8) |
		((val & (uint64_t)0x000000ff00000000ULL) >>  8) |
		((val & (uint64_t)0x0000ff0000000000ULL) >> 24) |
		((val & (uint64_t)0x00ff000000000000ULL) >> 40) |
		((val & (uint64_t)0xff00000000000000ULL) >> 56));
}