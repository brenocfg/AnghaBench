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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 swab32(u32 x)
{
	return  ((x & (u32)0x000000ffUL) << 24) |
		((x & (u32)0x0000ff00UL) <<  8) |
		((x & (u32)0x00ff0000UL) >>  8) |
		((x & (u32)0xff000000UL) >> 24);
}