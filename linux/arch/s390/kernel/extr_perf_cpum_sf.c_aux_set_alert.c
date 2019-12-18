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
struct aux_buffer {int dummy; } ;

/* Variables and functions */
 unsigned long long SDB_TE_ALERT_REQ_MASK ; 
 unsigned long long SDB_TE_BUFFER_FULL_MASK ; 
 struct hws_trailer_entry* aux_sdb_trailer (struct aux_buffer*,unsigned long) ; 
 int /*<<< orphan*/  cmpxchg_double (unsigned long long*,unsigned long long*,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static bool aux_set_alert(struct aux_buffer *aux, unsigned long alert_index,
			  unsigned long long *overflow)
{
	unsigned long long orig_overflow, orig_flags, new_flags;
	struct hws_trailer_entry *te;

	te = aux_sdb_trailer(aux, alert_index);
	do {
		orig_flags = te->flags;
		orig_overflow = te->overflow;
		*overflow = orig_overflow;
		if (orig_flags & SDB_TE_BUFFER_FULL_MASK) {
			/*
			 * SDB is already set by hardware.
			 * Abort and try to set somewhere
			 * behind.
			 */
			return false;
		}
		new_flags = orig_flags | SDB_TE_ALERT_REQ_MASK;
	} while (!cmpxchg_double(&te->flags, &te->overflow,
				 orig_flags, orig_overflow,
				 new_flags, 0ULL));
	return true;
}