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
struct memtype {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {scalar_t__ (* is_untracked_pat_range ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct memtype*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__) ; 
 int free_ram_pages_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct memtype*) ; 
 int /*<<< orphan*/  memtype_lock ; 
 int /*<<< orphan*/  pat_enabled () ; 
 int pat_pagerange_is_ram (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct memtype* rbt_memtype_erase (scalar_t__,scalar_t__) ; 
 scalar_t__ sanitize_phys (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 TYPE_1__ x86_platform ; 

int free_memtype(u64 start, u64 end)
{
	int err = -EINVAL;
	int is_range_ram;
	struct memtype *entry;

	if (!pat_enabled())
		return 0;

	start = sanitize_phys(start);
	end = sanitize_phys(end);

	/* Low ISA region is always mapped WB. No need to track */
	if (x86_platform.is_untracked_pat_range(start, end))
		return 0;

	is_range_ram = pat_pagerange_is_ram(start, end);
	if (is_range_ram == 1) {

		err = free_ram_pages_type(start, end);

		return err;
	} else if (is_range_ram < 0) {
		return -EINVAL;
	}

	spin_lock(&memtype_lock);
	entry = rbt_memtype_erase(start, end);
	spin_unlock(&memtype_lock);

	if (IS_ERR(entry)) {
		pr_info("x86/PAT: %s:%d freeing invalid memtype [mem %#010Lx-%#010Lx]\n",
			current->comm, current->pid, start, end - 1);
		return -EINVAL;
	}

	kfree(entry);

	dprintk("free_memtype request [mem %#010Lx-%#010Lx]\n", start, end - 1);

	return 0;
}