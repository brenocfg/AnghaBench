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
struct ghes {int dummy; } ;
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ghes_in_nmi_queue_one_entry (struct ghes*,int) ; 
 int /*<<< orphan*/  ghes_proc_irq_work ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ghes_sdei_callback(struct ghes *ghes,
				enum fixed_addresses fixmap_idx)
{
	if (!ghes_in_nmi_queue_one_entry(ghes, fixmap_idx)) {
		irq_work_queue(&ghes_proc_irq_work);

		return 0;
	}

	return -ENOENT;
}