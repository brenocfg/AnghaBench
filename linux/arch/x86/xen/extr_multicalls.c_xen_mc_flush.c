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
struct multicall_entry {scalar_t__ result; int /*<<< orphan*/ * args; int /*<<< orphan*/  op; } ;
struct mc_buffer {int mcidx; scalar_t__ argidx; int cbidx; struct callback* callbacks; struct multicall_entry* entries; int /*<<< orphan*/ * caller; TYPE_1__* debug; } ;
struct callback {int /*<<< orphan*/  data; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * args; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HYPERVISOR_multicall (struct multicall_entry*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mc_buffer ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct multicall_entry*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ,...) ; 
 int preemptible () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct mc_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xen_mc_flush (int,scalar_t__,int) ; 
 scalar_t__ xen_single_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xen_mc_flush(void)
{
	struct mc_buffer *b = this_cpu_ptr(&mc_buffer);
	struct multicall_entry *mc;
	int ret = 0;
	unsigned long flags;
	int i;

	BUG_ON(preemptible());

	/* Disable interrupts in case someone comes in and queues
	   something in the middle */
	local_irq_save(flags);

	trace_xen_mc_flush(b->mcidx, b->argidx, b->cbidx);

#if MC_DEBUG
	memcpy(b->debug, b->entries,
	       b->mcidx * sizeof(struct multicall_entry));
#endif

	switch (b->mcidx) {
	case 0:
		/* no-op */
		BUG_ON(b->argidx != 0);
		break;

	case 1:
		/* Singleton multicall - bypass multicall machinery
		   and just do the call directly. */
		mc = &b->entries[0];

		mc->result = xen_single_call(mc->op, mc->args[0], mc->args[1],
					     mc->args[2], mc->args[3],
					     mc->args[4]);
		ret = mc->result < 0;
		break;

	default:
		if (HYPERVISOR_multicall(b->entries, b->mcidx) != 0)
			BUG();
		for (i = 0; i < b->mcidx; i++)
			if (b->entries[i].result < 0)
				ret++;
	}

	if (WARN_ON(ret)) {
		pr_err("%d of %d multicall(s) failed: cpu %d\n",
		       ret, b->mcidx, smp_processor_id());
		for (i = 0; i < b->mcidx; i++) {
			if (b->entries[i].result < 0) {
#if MC_DEBUG
				pr_err("  call %2d: op=%lu arg=[%lx] result=%ld\t%pS\n",
				       i + 1,
				       b->debug[i].op,
				       b->debug[i].args[0],
				       b->entries[i].result,
				       b->caller[i]);
#else
				pr_err("  call %2d: op=%lu arg=[%lx] result=%ld\n",
				       i + 1,
				       b->entries[i].op,
				       b->entries[i].args[0],
				       b->entries[i].result);
#endif
			}
		}
	}

	b->mcidx = 0;
	b->argidx = 0;

	for (i = 0; i < b->cbidx; i++) {
		struct callback *cb = &b->callbacks[i];

		(*cb->fn)(cb->data);
	}
	b->cbidx = 0;

	local_irq_restore(flags);
}