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
struct notifier_block {int dummy; } ;
struct mce {scalar_t__ severity; unsigned long addr; } ;

/* Variables and functions */
 scalar_t__ MCE_AO_SEVERITY ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ mce_usable_address (struct mce*) ; 
 int /*<<< orphan*/  memory_failure (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mce_nospec (unsigned long) ; 

__attribute__((used)) static int srao_decode_notifier(struct notifier_block *nb, unsigned long val,
				void *data)
{
	struct mce *mce = (struct mce *)data;
	unsigned long pfn;

	if (!mce)
		return NOTIFY_DONE;

	if (mce_usable_address(mce) && (mce->severity == MCE_AO_SEVERITY)) {
		pfn = mce->addr >> PAGE_SHIFT;
		if (!memory_failure(pfn, 0))
			set_mce_nospec(pfn);
	}

	return NOTIFY_OK;
}