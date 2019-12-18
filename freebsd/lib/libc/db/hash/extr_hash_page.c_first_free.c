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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 scalar_t__ BITS_PER_MAP ; 

__attribute__((used)) static u_int32_t
first_free(u_int32_t map)
{
	u_int32_t i, mask;

	mask = 0x1;
	for (i = 0; i < BITS_PER_MAP; i++) {
		if (!(mask & map))
			return (i);
		mask = mask << 1;
	}
	return (i);
}