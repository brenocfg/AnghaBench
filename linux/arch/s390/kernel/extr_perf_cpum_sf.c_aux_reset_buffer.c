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
struct hws_trailer_entry {unsigned long long flags; unsigned long long overflow; } ;
struct aux_buffer {unsigned long alert_mark; unsigned long empty_mark; int head; } ;

/* Variables and functions */
 unsigned long AUX_SDB_NUM_EMPTY (struct aux_buffer*) ; 
 unsigned long long SDB_TE_ALERT_REQ_MASK ; 
 unsigned long long SDB_TE_BUFFER_FULL_MASK ; 
 struct hws_trailer_entry* aux_sdb_trailer (struct aux_buffer*,unsigned long) ; 
 int aux_set_alert (struct aux_buffer*,unsigned long,unsigned long long*) ; 
 int /*<<< orphan*/  cmpxchg_double (unsigned long long*,unsigned long long*,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static bool aux_reset_buffer(struct aux_buffer *aux, unsigned long range,
			     unsigned long long *overflow)
{
	unsigned long long orig_overflow, orig_flags, new_flags;
	unsigned long i, range_scan, idx;
	struct hws_trailer_entry *te;

	if (range <= AUX_SDB_NUM_EMPTY(aux))
		/*
		 * No need to scan. All SDBs in range are marked as empty.
		 * Just set alert indicator. Should check race with hardware
		 * sampler.
		 */
		return aux_set_alert(aux, aux->alert_mark, overflow);

	if (aux->alert_mark <= aux->empty_mark)
		/*
		 * Set alert indicator on empty SDB. Should check race
		 * with hardware sampler.
		 */
		if (!aux_set_alert(aux, aux->alert_mark, overflow))
			return false;

	/*
	 * Scan the SDBs to clear full and alert indicator used previously.
	 * Start scanning from one SDB behind empty_mark. If the new alert
	 * indicator fall into this range, set it.
	 */
	range_scan = range - AUX_SDB_NUM_EMPTY(aux);
	idx = aux->empty_mark + 1;
	for (i = 0; i < range_scan; i++, idx++) {
		te = aux_sdb_trailer(aux, idx);
		do {
			orig_flags = te->flags;
			orig_overflow = te->overflow;
			new_flags = orig_flags & ~SDB_TE_BUFFER_FULL_MASK;
			if (idx == aux->alert_mark)
				new_flags |= SDB_TE_ALERT_REQ_MASK;
			else
				new_flags &= ~SDB_TE_ALERT_REQ_MASK;
		} while (!cmpxchg_double(&te->flags, &te->overflow,
					 orig_flags, orig_overflow,
					 new_flags, 0ULL));
		*overflow += orig_overflow;
	}

	/* Update empty_mark to new position */
	aux->empty_mark = aux->head + range - 1;

	return true;
}