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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ pcib_bit_get (scalar_t__*,scalar_t__) ; 

__attribute__((used)) static inline uint32_t
pcib_map_check(uint32_t *map, uint32_t start, uint32_t bits)
{
	uint32_t i;

	for (i = start; i < start + bits; i++)
		if (pcib_bit_get(map, i))
			return (0);

	return (1);
}