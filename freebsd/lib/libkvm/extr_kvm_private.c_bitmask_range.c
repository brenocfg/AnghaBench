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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ BITS_IN (scalar_t__) ; 

__attribute__((used)) static uint64_t
bitmask_range(uint64_t v, uint64_t bit0, uint64_t bitN)
{
	if (bit0 == 0 && bitN == BITS_IN(v))
		return (v);

	return (v & (((1ULL << (bitN - bit0)) - 1ULL) << bit0));
}