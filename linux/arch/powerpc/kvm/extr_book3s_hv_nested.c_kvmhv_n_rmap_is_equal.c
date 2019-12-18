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
 int RMAP_NESTED_GPA_MASK ; 
 int RMAP_NESTED_LPID_MASK ; 

__attribute__((used)) static inline bool kvmhv_n_rmap_is_equal(u64 rmap_1, u64 rmap_2)
{
	return !((rmap_1 ^ rmap_2) & (RMAP_NESTED_LPID_MASK |
				       RMAP_NESTED_GPA_MASK));
}