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
struct s390_map_info {int guest_addr; int /*<<< orphan*/  page; int /*<<< orphan*/  addr; } ;
struct s390_io_adapter {int /*<<< orphan*/  swap; } ;
struct kvm_s390_adapter_int {int /*<<< orphan*/  summary_offset; int /*<<< orphan*/  summary_addr; int /*<<< orphan*/  ind_offset; int /*<<< orphan*/  ind_addr; } ;
struct kvm {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long get_ind_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s390_map_info* get_map_info (struct s390_io_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_dirty (struct kvm*,int) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned long,void*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int test_and_set_bit (unsigned long,void*) ; 

__attribute__((used)) static int adapter_indicators_set(struct kvm *kvm,
				  struct s390_io_adapter *adapter,
				  struct kvm_s390_adapter_int *adapter_int)
{
	unsigned long bit;
	int summary_set, idx;
	struct s390_map_info *info;
	void *map;

	info = get_map_info(adapter, adapter_int->ind_addr);
	if (!info)
		return -1;
	map = page_address(info->page);
	bit = get_ind_bit(info->addr, adapter_int->ind_offset, adapter->swap);
	set_bit(bit, map);
	idx = srcu_read_lock(&kvm->srcu);
	mark_page_dirty(kvm, info->guest_addr >> PAGE_SHIFT);
	set_page_dirty_lock(info->page);
	info = get_map_info(adapter, adapter_int->summary_addr);
	if (!info) {
		srcu_read_unlock(&kvm->srcu, idx);
		return -1;
	}
	map = page_address(info->page);
	bit = get_ind_bit(info->addr, adapter_int->summary_offset,
			  adapter->swap);
	summary_set = test_and_set_bit(bit, map);
	mark_page_dirty(kvm, info->guest_addr >> PAGE_SHIFT);
	set_page_dirty_lock(info->page);
	srcu_read_unlock(&kvm->srcu, idx);
	return summary_set ? 0 : 1;
}