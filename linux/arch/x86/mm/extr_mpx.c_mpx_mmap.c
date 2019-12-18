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
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  VM_MPX ; 
 TYPE_1__* current ; 
 unsigned long do_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_populate (unsigned long,unsigned long) ; 
 unsigned long mpx_bt_size_bytes (struct mm_struct*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long mpx_mmap(unsigned long len)
{
	struct mm_struct *mm = current->mm;
	unsigned long addr, populate;

	/* Only bounds table can be allocated here */
	if (len != mpx_bt_size_bytes(mm))
		return -EINVAL;

	down_write(&mm->mmap_sem);
	addr = do_mmap(NULL, 0, len, PROT_READ | PROT_WRITE,
		       MAP_ANONYMOUS | MAP_PRIVATE, VM_MPX, 0, &populate, NULL);
	up_write(&mm->mmap_sem);
	if (populate)
		mm_populate(addr, populate);

	return addr;
}