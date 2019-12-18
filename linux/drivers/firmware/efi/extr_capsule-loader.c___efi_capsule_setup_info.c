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
struct TYPE_2__ {int /*<<< orphan*/  imagesize; int /*<<< orphan*/  flags; int /*<<< orphan*/  guid; } ;
struct capsule_info {void* phys; void* pages; int /*<<< orphan*/  reset_type; TYPE_1__ header; int /*<<< orphan*/  total_size; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,size_t) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int efi_capsule_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* krealloc (void*,size_t,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int __efi_capsule_setup_info(struct capsule_info *cap_info)
{
	size_t pages_needed;
	int ret;
	void *temp_page;

	pages_needed = ALIGN(cap_info->total_size, PAGE_SIZE) / PAGE_SIZE;

	if (pages_needed == 0) {
		pr_err("invalid capsule size\n");
		return -EINVAL;
	}

	/* Check if the capsule binary supported */
	ret = efi_capsule_supported(cap_info->header.guid,
				    cap_info->header.flags,
				    cap_info->header.imagesize,
				    &cap_info->reset_type);
	if (ret) {
		pr_err("capsule not supported\n");
		return ret;
	}

	temp_page = krealloc(cap_info->pages,
			     pages_needed * sizeof(void *),
			     GFP_KERNEL | __GFP_ZERO);
	if (!temp_page)
		return -ENOMEM;

	cap_info->pages = temp_page;

	temp_page = krealloc(cap_info->phys,
			     pages_needed * sizeof(phys_addr_t *),
			     GFP_KERNEL | __GFP_ZERO);
	if (!temp_page)
		return -ENOMEM;

	cap_info->phys = temp_page;

	return 0;
}