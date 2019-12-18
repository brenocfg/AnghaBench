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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct hv_vp_assist_page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  HV_X64_MSR_VP_ASSIST_PAGE ; 
 scalar_t__ HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT ; 
 scalar_t__ HV_X64_MSR_VP_ASSIST_PAGE_ENABLE ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct hv_vp_assist_page* __vmalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  hv_get_vp_index (scalar_t__) ; 
 scalar_t__ hv_max_vp_index ; 
 struct hv_vp_assist_page** hv_vp_assist_page ; 
 scalar_t__* hv_vp_index ; 
 int /*<<< orphan*/  hyperv_pcpu_input_arg ; 
 void* page_address (struct page*) ; 
 size_t smp_processor_id () ; 
 scalar_t__ this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vmalloc_to_pfn (struct hv_vp_assist_page*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hv_cpu_init(unsigned int cpu)
{
	u64 msr_vp_index;
	struct hv_vp_assist_page **hvp = &hv_vp_assist_page[smp_processor_id()];
	void **input_arg;
	struct page *pg;

	input_arg = (void **)this_cpu_ptr(hyperv_pcpu_input_arg);
	pg = alloc_page(GFP_KERNEL);
	if (unlikely(!pg))
		return -ENOMEM;
	*input_arg = page_address(pg);

	hv_get_vp_index(msr_vp_index);

	hv_vp_index[smp_processor_id()] = msr_vp_index;

	if (msr_vp_index > hv_max_vp_index)
		hv_max_vp_index = msr_vp_index;

	if (!hv_vp_assist_page)
		return 0;

	/*
	 * The VP ASSIST PAGE is an "overlay" page (see Hyper-V TLFS's Section
	 * 5.2.1 "GPA Overlay Pages"). Here it must be zeroed out to make sure
	 * we always write the EOI MSR in hv_apic_eoi_write() *after* the
	 * EOI optimization is disabled in hv_cpu_die(), otherwise a CPU may
	 * not be stopped in the case of CPU offlining and the VM will hang.
	 */
	if (!*hvp) {
		*hvp = __vmalloc(PAGE_SIZE, GFP_KERNEL | __GFP_ZERO,
				 PAGE_KERNEL);
	}

	if (*hvp) {
		u64 val;

		val = vmalloc_to_pfn(*hvp);
		val = (val << HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT) |
			HV_X64_MSR_VP_ASSIST_PAGE_ENABLE;

		wrmsrl(HV_X64_MSR_VP_ASSIST_PAGE, val);
	}

	return 0;
}