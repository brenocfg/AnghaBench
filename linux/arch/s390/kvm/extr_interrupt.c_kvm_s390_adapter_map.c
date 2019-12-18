#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s390_map_info {int addr; int /*<<< orphan*/  page; int /*<<< orphan*/  list; int /*<<< orphan*/  guest_addr; } ;
struct s390_io_adapter {int /*<<< orphan*/  maps_lock; int /*<<< orphan*/  maps; int /*<<< orphan*/  nr_maps; } ;
struct TYPE_2__ {int /*<<< orphan*/  gmap; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_S390_ADAPTER_MAPS ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct s390_io_adapter* get_io_adapter (struct kvm*,unsigned int) ; 
 int get_user_pages_fast (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gmap_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s390_map_info*) ; 
 struct s390_map_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_s390_adapter_map(struct kvm *kvm, unsigned int id, __u64 addr)
{
	struct s390_io_adapter *adapter = get_io_adapter(kvm, id);
	struct s390_map_info *map;
	int ret;

	if (!adapter || !addr)
		return -EINVAL;

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (!map) {
		ret = -ENOMEM;
		goto out;
	}
	INIT_LIST_HEAD(&map->list);
	map->guest_addr = addr;
	map->addr = gmap_translate(kvm->arch.gmap, addr);
	if (map->addr == -EFAULT) {
		ret = -EFAULT;
		goto out;
	}
	ret = get_user_pages_fast(map->addr, 1, FOLL_WRITE, &map->page);
	if (ret < 0)
		goto out;
	BUG_ON(ret != 1);
	down_write(&adapter->maps_lock);
	if (atomic_inc_return(&adapter->nr_maps) < MAX_S390_ADAPTER_MAPS) {
		list_add_tail(&map->list, &adapter->maps);
		ret = 0;
	} else {
		put_page(map->page);
		ret = -EINVAL;
	}
	up_write(&adapter->maps_lock);
out:
	if (ret)
		kfree(map);
	return ret;
}