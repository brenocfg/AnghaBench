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
struct cpa_data {scalar_t__ force_split; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int __should_split_large_page (int /*<<< orphan*/ *,unsigned long,struct cpa_data*) ; 
 int /*<<< orphan*/  pgd_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int should_split_large_page(pte_t *kpte, unsigned long address,
				   struct cpa_data *cpa)
{
	int do_split;

	if (cpa->force_split)
		return 1;

	spin_lock(&pgd_lock);
	do_split = __should_split_large_page(kpte, address, cpa);
	spin_unlock(&pgd_lock);

	return do_split;
}