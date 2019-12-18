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
struct dcss_segment {int do_nonshared; unsigned long start_addr; unsigned long end; int vm_segtype; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int ENOSYS ; 
 int EPERM ; 
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int __segment_load (char*,int,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  dcss_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 struct dcss_segment* segment_by_name (char*) ; 

int
segment_load (char *name, int do_nonshared, unsigned long *addr,
		unsigned long *end)
{
	struct dcss_segment *seg;
	int rc;

	if (!MACHINE_IS_VM)
		return -ENOSYS;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	if (seg == NULL)
		rc = __segment_load (name, do_nonshared, addr, end);
	else {
		if (do_nonshared == seg->do_nonshared) {
			refcount_inc(&seg->ref_count);
			*addr = seg->start_addr;
			*end  = seg->end;
			rc    = seg->vm_segtype;
		} else {
			*addr = *end = 0;
			rc    = -EPERM;
		}
	}
	mutex_unlock(&dcss_lock);
	return rc;
}