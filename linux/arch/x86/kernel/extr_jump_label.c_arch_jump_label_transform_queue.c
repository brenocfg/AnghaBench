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
typedef  union jump_code_union {int dummy; } jump_code_union ;
struct text_poke_loc {void* addr; int len; void* detour; int /*<<< orphan*/  opcode; } ;
struct jump_entry {int dummy; } ;
typedef  enum jump_label_type { ____Placeholder_jump_label_type } jump_label_type ;

/* Variables and functions */
 int JUMP_LABEL_NOP_SIZE ; 
 scalar_t__ SYSTEM_BOOTING ; 
 size_t TP_VEC_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __jump_label_set_jump_code (struct jump_entry*,int,union jump_code_union*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_jump_label_transform (struct jump_entry*,int) ; 
 scalar_t__ jump_entry_code (struct jump_entry*) ; 
 scalar_t__ system_state ; 
 struct text_poke_loc* tp_vec ; 
 size_t tp_vec_nr ; 

bool arch_jump_label_transform_queue(struct jump_entry *entry,
				     enum jump_label_type type)
{
	struct text_poke_loc *tp;
	void *entry_code;

	if (system_state == SYSTEM_BOOTING) {
		/*
		 * Fallback to the non-batching mode.
		 */
		arch_jump_label_transform(entry, type);
		return true;
	}

	/*
	 * No more space in the vector, tell upper layer to apply
	 * the queue before continuing.
	 */
	if (tp_vec_nr == TP_VEC_MAX)
		return false;

	tp = &tp_vec[tp_vec_nr];

	entry_code = (void *)jump_entry_code(entry);

	/*
	 * The INT3 handler will do a bsearch in the queue, so we need entries
	 * to be sorted. We can survive an unsorted list by rejecting the entry,
	 * forcing the generic jump_label code to apply the queue. Warning once,
	 * to raise the attention to the case of an unsorted entry that is
	 * better not happen, because, in the worst case we will perform in the
	 * same way as we do without batching - with some more overhead.
	 */
	if (tp_vec_nr > 0) {
		int prev = tp_vec_nr - 1;
		struct text_poke_loc *prev_tp = &tp_vec[prev];

		if (WARN_ON_ONCE(prev_tp->addr > entry_code))
			return false;
	}

	__jump_label_set_jump_code(entry, type,
				   (union jump_code_union *) &tp->opcode, 0);

	tp->addr = entry_code;
	tp->detour = entry_code + JUMP_LABEL_NOP_SIZE;
	tp->len = JUMP_LABEL_NOP_SIZE;

	tp_vec_nr++;

	return true;
}