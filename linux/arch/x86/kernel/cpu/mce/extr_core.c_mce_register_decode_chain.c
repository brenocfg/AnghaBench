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
struct notifier_block {scalar_t__ priority; } ;

/* Variables and functions */
 scalar_t__ MCE_PRIO_EDAC ; 
 scalar_t__ MCE_PRIO_MCELOG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  num_notifiers ; 
 int /*<<< orphan*/  x86_mce_decoder_chain ; 

void mce_register_decode_chain(struct notifier_block *nb)
{
	if (WARN_ON(nb->priority > MCE_PRIO_MCELOG && nb->priority < MCE_PRIO_EDAC))
		return;

	atomic_inc(&num_notifiers);

	blocking_notifier_chain_register(&x86_mce_decoder_chain, nb);
}