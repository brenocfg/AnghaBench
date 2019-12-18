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
combine_surrogate_pair(uint32_t uc, uint32_t uc2)
{
	uc -= 0xD800;
	uc *= 0x400;
	uc += uc2 - 0xDC00;
	uc += 0x10000;
	return (uc);
}