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
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static inline int32_t sign_extend(uint32_t value, int index)
{
	uint8_t shift;

	shift = 31 - index;
	return ((int32_t)(value << shift) >> shift);
}