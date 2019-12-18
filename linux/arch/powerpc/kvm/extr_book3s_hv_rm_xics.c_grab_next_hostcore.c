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
union kvmppc_rm_state {int rm_action; scalar_t__ raw; int /*<<< orphan*/  in_host; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct kvmppc_host_rm_core {TYPE_1__ rm_state; } ;

/* Variables and functions */
 union kvmppc_rm_state READ_ONCE (TYPE_1__) ; 
 scalar_t__ cmpxchg64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline int grab_next_hostcore(int start,
		struct kvmppc_host_rm_core *rm_core, int max, int action)
{
	bool success;
	int core;
	union kvmppc_rm_state old, new;

	for (core = start + 1; core < max; core++)  {
		old = new = READ_ONCE(rm_core[core].rm_state);

		if (!old.in_host || old.rm_action)
			continue;

		/* Try to grab this host core if not taken already. */
		new.rm_action = action;

		success = cmpxchg64(&rm_core[core].rm_state.raw,
						old.raw, new.raw) == old.raw;
		if (success) {
			/*
			 * Make sure that the store to the rm_action is made
			 * visible before we return to caller (and the
			 * subsequent store to rm_data) to synchronize with
			 * the IPI handler.
			 */
			smp_wmb();
			return core;
		}
	}

	return -1;
}