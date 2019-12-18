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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
byteswap32(uint32_t v)
{

	return ((v & 0xff000000) >> 24 | (v & 0x00ff0000) >> 8 |
	    (v & 0x0000ff00) << 8 | (v & 0x000000ff) << 24);
}