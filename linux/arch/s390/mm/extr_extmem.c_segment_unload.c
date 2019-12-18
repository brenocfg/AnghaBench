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
struct dcss_segment {int /*<<< orphan*/  dcss_name; int /*<<< orphan*/  list; scalar_t__ start_addr; scalar_t__ end; struct dcss_segment* res; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int /*<<< orphan*/  dcss_diag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  dcss_lock ; 
 int /*<<< orphan*/  kfree (struct dcss_segment*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  purgeseg_scode ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (struct dcss_segment*) ; 
 struct dcss_segment* segment_by_name (char*) ; 
 int /*<<< orphan*/  vmem_remove_mapping (scalar_t__,scalar_t__) ; 

void
segment_unload(char *name)
{
	unsigned long dummy;
	struct dcss_segment *seg;

	if (!MACHINE_IS_VM)
		return;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	if (seg == NULL) {
		pr_err("Unloading unknown DCSS %s failed\n", name);
		goto out_unlock;
	}
	if (!refcount_dec_and_test(&seg->ref_count))
		goto out_unlock;
	release_resource(seg->res);
	kfree(seg->res);
	vmem_remove_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
	list_del(&seg->list);
	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kfree(seg);
out_unlock:
	mutex_unlock(&dcss_lock);
}