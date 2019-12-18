#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct qlnxr_ucontext {int /*<<< orphan*/  mm_list_lock; int /*<<< orphan*/  mm_head; TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ phy_addr; } ;
struct qlnxr_mm {TYPE_2__ key; int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ha; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct qlnxr_mm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ roundup (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnxr_add_mmap(struct qlnxr_ucontext *uctx, u64 phy_addr, unsigned long len)
{
	struct qlnxr_mm	*mm;
	qlnx_host_t	*ha;

	ha = uctx->dev->ha;

	QL_DPRINT12(ha, "enter\n");

	mm = kzalloc(sizeof(*mm), GFP_KERNEL);
	if (mm == NULL) {
		QL_DPRINT11(ha, "mm = NULL\n");
		return -ENOMEM;
	}

	mm->key.phy_addr = phy_addr;

	/* This function might be called with a length which is not a multiple
	 * of PAGE_SIZE, while the mapping is PAGE_SIZE grained and the kernel
	 * forces this granularity by increasing the requested size if needed.
	 * When qedr_mmap is called, it will search the list with the updated
	 * length as a key. To prevent search failures, the length is rounded up
	 * in advance to PAGE_SIZE.
	 */
	mm->key.len = roundup(len, PAGE_SIZE);
	INIT_LIST_HEAD(&mm->entry);

	mutex_lock(&uctx->mm_list_lock);
	list_add(&mm->entry, &uctx->mm_head);
	mutex_unlock(&uctx->mm_list_lock);

	QL_DPRINT12(ha, "added (addr=0x%llx,len=0x%lx) for ctx=%p\n",
		(unsigned long long)mm->key.phy_addr,
		(unsigned long)mm->key.len, uctx);

	return 0;
}