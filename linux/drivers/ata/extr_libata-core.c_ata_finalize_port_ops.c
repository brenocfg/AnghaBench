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
struct ata_port_operations {struct ata_port_operations* inherits; } ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ata_finalize_port_ops(struct ata_port_operations *ops)
{
	static DEFINE_SPINLOCK(lock);
	const struct ata_port_operations *cur;
	void **begin = (void **)ops;
	void **end = (void **)&ops->inherits;
	void **pp;

	if (!ops || !ops->inherits)
		return;

	spin_lock(&lock);

	for (cur = ops->inherits; cur; cur = cur->inherits) {
		void **inherit = (void **)cur;

		for (pp = begin; pp < end; pp++, inherit++)
			if (!*pp)
				*pp = *inherit;
	}

	for (pp = begin; pp < end; pp++)
		if (IS_ERR(*pp))
			*pp = NULL;

	ops->inherits = NULL;

	spin_unlock(&lock);
}