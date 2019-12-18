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
struct spu {int /*<<< orphan*/  number; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_lock ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int process_context_switch (struct spu*,unsigned long) ; 
 int release_cached_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int spu_active_notify(struct notifier_block *self, unsigned long val,
				void *data)
{
	int retval;
	unsigned long flags;
	struct spu *the_spu = data;

	pr_debug("SPU event notification arrived\n");
	if (!val) {
		spin_lock_irqsave(&cache_lock, flags);
		retval = release_cached_info(the_spu->number);
		spin_unlock_irqrestore(&cache_lock, flags);
	} else {
		retval = process_context_switch(the_spu, val);
	}
	return retval;
}