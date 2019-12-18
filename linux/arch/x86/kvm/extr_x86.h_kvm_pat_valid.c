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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static inline bool kvm_pat_valid(u64 data)
{
	if (data & 0xF8F8F8F8F8F8F8F8ull)
		return false;
	/* 0, 1, 4, 5, 6, 7 are valid values.  */
	return (data | ((data & 0x0202020202020202ull) << 1)) == data;
}