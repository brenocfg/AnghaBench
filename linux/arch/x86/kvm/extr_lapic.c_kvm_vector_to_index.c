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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int find_next_bit (unsigned long const*,int,int) ; 

int kvm_vector_to_index(u32 vector, u32 dest_vcpus,
		       const unsigned long *bitmap, u32 bitmap_size)
{
	u32 mod;
	int i, idx = -1;

	mod = vector % dest_vcpus;

	for (i = 0; i <= mod; i++) {
		idx = find_next_bit(bitmap, bitmap_size, idx + 1);
		BUG_ON(idx == bitmap_size);
	}

	return idx;
}