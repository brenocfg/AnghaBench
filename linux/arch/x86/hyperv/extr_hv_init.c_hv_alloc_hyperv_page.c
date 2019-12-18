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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HV_HYP_PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 

void *hv_alloc_hyperv_page(void)
{
	BUILD_BUG_ON(PAGE_SIZE != HV_HYP_PAGE_SIZE);

	return (void *)__get_free_page(GFP_KERNEL);
}