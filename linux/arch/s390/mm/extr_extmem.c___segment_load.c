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
struct resource {int dummy; } ;
struct dcss_segment {unsigned long start_addr; unsigned long end; int flags; unsigned long start; char* res_name; char* name; int vm_segtype; int do_nonshared; struct dcss_segment* res; int /*<<< orphan*/  list; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  dcss_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int IORESOURCE_BUSY ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_READONLY ; 
 int SEG_TYPE_ER ; 
 int SEG_TYPE_SC ; 
 int SEG_TYPE_SR ; 
 int dcss_diag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int dcss_diag_translate_rc (unsigned long) ; 
 int /*<<< orphan*/  dcss_list ; 
 int /*<<< orphan*/  dcss_mkname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  kfree (struct dcss_segment*) ; 
 struct dcss_segment* kmalloc (int,int) ; 
 struct dcss_segment* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loadnsr_scode ; 
 int /*<<< orphan*/  loadshr_scode ; 
 int /*<<< orphan*/  memcpy (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  purgeseg_scode ; 
 int query_segment_type (struct dcss_segment*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_resource (struct dcss_segment*) ; 
 scalar_t__ request_resource (int /*<<< orphan*/ *,struct dcss_segment*) ; 
 scalar_t__ segment_overlaps_others (struct dcss_segment*) ; 
 int /*<<< orphan*/ * segtype_string ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int vmem_add_mapping (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vmem_remove_mapping (unsigned long,unsigned long) ; 

__attribute__((used)) static int
__segment_load (char *name, int do_nonshared, unsigned long *addr, unsigned long *end)
{
	unsigned long start_addr, end_addr, dummy;
	struct dcss_segment *seg;
	int rc, diag_cc;

	start_addr = end_addr = 0;
	seg = kmalloc(sizeof(*seg), GFP_KERNEL | GFP_DMA);
	if (seg == NULL) {
		rc = -ENOMEM;
		goto out;
	}
	dcss_mkname (name, seg->dcss_name);
	rc = query_segment_type (seg);
	if (rc < 0)
		goto out_free;

	if (segment_overlaps_others(seg)) {
		rc = -EBUSY;
		goto out_free;
	}

	rc = vmem_add_mapping(seg->start_addr, seg->end - seg->start_addr + 1);

	if (rc)
		goto out_free;

	seg->res = kzalloc(sizeof(struct resource), GFP_KERNEL);
	if (seg->res == NULL) {
		rc = -ENOMEM;
		goto out_shared;
	}
	seg->res->flags = IORESOURCE_BUSY | IORESOURCE_MEM;
	seg->res->start = seg->start_addr;
	seg->res->end = seg->end;
	memcpy(&seg->res_name, seg->dcss_name, 8);
	EBCASC(seg->res_name, 8);
	seg->res_name[8] = '\0';
	strlcat(seg->res_name, " (DCSS)", sizeof(seg->res_name));
	seg->res->name = seg->res_name;
	rc = seg->vm_segtype;
	if (rc == SEG_TYPE_SC ||
	    ((rc == SEG_TYPE_SR || rc == SEG_TYPE_ER) && !do_nonshared))
		seg->res->flags |= IORESOURCE_READONLY;
	if (request_resource(&iomem_resource, seg->res)) {
		rc = -EBUSY;
		kfree(seg->res);
		goto out_shared;
	}

	if (do_nonshared)
		diag_cc = dcss_diag(&loadnsr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	else
		diag_cc = dcss_diag(&loadshr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	if (diag_cc < 0) {
		dcss_diag(&purgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		rc = diag_cc;
		goto out_resource;
	}
	if (diag_cc > 1) {
		pr_warn("Loading DCSS %s failed with rc=%ld\n", name, end_addr);
		rc = dcss_diag_translate_rc(end_addr);
		dcss_diag(&purgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		goto out_resource;
	}
	seg->start_addr = start_addr;
	seg->end = end_addr;
	seg->do_nonshared = do_nonshared;
	refcount_set(&seg->ref_count, 1);
	list_add(&seg->list, &dcss_list);
	*addr = seg->start_addr;
	*end  = seg->end;
	if (do_nonshared)
		pr_info("DCSS %s of range %px to %px and type %s loaded as "
			"exclusive-writable\n", name, (void*) seg->start_addr,
			(void*) seg->end, segtype_string[seg->vm_segtype]);
	else {
		pr_info("DCSS %s of range %px to %px and type %s loaded in "
			"shared access mode\n", name, (void*) seg->start_addr,
			(void*) seg->end, segtype_string[seg->vm_segtype]);
	}
	goto out;
 out_resource:
	release_resource(seg->res);
	kfree(seg->res);
 out_shared:
	vmem_remove_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
 out_free:
	kfree(seg);
 out:
	return rc;
}