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
struct dcss_segment {int do_nonshared; scalar_t__ vm_segtype; unsigned long start_addr; unsigned long end; int /*<<< orphan*/  dcss_name; int /*<<< orphan*/  list; struct dcss_segment* res; int /*<<< orphan*/  flags; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_READONLY ; 
 scalar_t__ SEG_TYPE_ER ; 
 scalar_t__ SEG_TYPE_SR ; 
 int dcss_diag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int dcss_diag_translate_rc (unsigned long) ; 
 int /*<<< orphan*/  dcss_lock ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  kfree (struct dcss_segment*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loadnsr_scode ; 
 int /*<<< orphan*/  loadshr_scode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,...) ; 
 int /*<<< orphan*/  purgeseg_scode ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (struct dcss_segment*) ; 
 scalar_t__ request_resource (int /*<<< orphan*/ *,struct dcss_segment*) ; 
 struct dcss_segment* segment_by_name (char*) ; 
 int /*<<< orphan*/  vmem_remove_mapping (unsigned long,unsigned long) ; 

int
segment_modify_shared (char *name, int do_nonshared)
{
	struct dcss_segment *seg;
	unsigned long start_addr, end_addr, dummy;
	int rc, diag_cc;

	start_addr = end_addr = 0;
	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	if (seg == NULL) {
		rc = -EINVAL;
		goto out_unlock;
	}
	if (do_nonshared == seg->do_nonshared) {
		pr_info("DCSS %s is already in the requested access "
			"mode\n", name);
		rc = 0;
		goto out_unlock;
	}
	if (refcount_read(&seg->ref_count) != 1) {
		pr_warn("DCSS %s is in use and cannot be reloaded\n", name);
		rc = -EAGAIN;
		goto out_unlock;
	}
	release_resource(seg->res);
	if (do_nonshared)
		seg->res->flags &= ~IORESOURCE_READONLY;
	else
		if (seg->vm_segtype == SEG_TYPE_SR ||
		    seg->vm_segtype == SEG_TYPE_ER)
			seg->res->flags |= IORESOURCE_READONLY;

	if (request_resource(&iomem_resource, seg->res)) {
		pr_warn("DCSS %s overlaps with used memory resources and cannot be reloaded\n",
			name);
		rc = -EBUSY;
		kfree(seg->res);
		goto out_del_mem;
	}

	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	if (do_nonshared)
		diag_cc = dcss_diag(&loadnsr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	else
		diag_cc = dcss_diag(&loadshr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	if (diag_cc < 0) {
		rc = diag_cc;
		goto out_del_res;
	}
	if (diag_cc > 1) {
		pr_warn("Reloading DCSS %s failed with rc=%ld\n",
			name, end_addr);
		rc = dcss_diag_translate_rc(end_addr);
		goto out_del_res;
	}
	seg->start_addr = start_addr;
	seg->end = end_addr;
	seg->do_nonshared = do_nonshared;
	rc = 0;
	goto out_unlock;
 out_del_res:
	release_resource(seg->res);
	kfree(seg->res);
 out_del_mem:
	vmem_remove_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
	list_del(&seg->list);
	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kfree(seg);
 out_unlock:
	mutex_unlock(&dcss_lock);
	return rc;
}