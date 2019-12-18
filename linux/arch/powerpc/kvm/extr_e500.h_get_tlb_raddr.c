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
struct kvm_book3e_206_tlb_entry {int mas7_3; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 get_tlb_raddr(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return tlbe->mas7_3 & ~0xfffULL;
}