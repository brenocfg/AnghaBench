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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct sctp_pcb {scalar_t__ initial_sequence_debug; int store_at; int /*<<< orphan*/ * random_store; } ;

/* Variables and functions */
 int SCTP_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 
 int /*<<< orphan*/  sctp_fill_random_store (struct sctp_pcb*) ; 

uint32_t
sctp_select_initial_TSN(struct sctp_pcb *inp)
{
	/*
	 * A true implementation should use random selection process to get
	 * the initial stream sequence number, using RFC1750 as a good
	 * guideline
	 */
	uint32_t x, *xp;
	uint8_t *p;
	int store_at, new_store;

	if (inp->initial_sequence_debug != 0) {
		uint32_t ret;

		ret = inp->initial_sequence_debug;
		inp->initial_sequence_debug++;
		return (ret);
	}
retry:
	store_at = inp->store_at;
	new_store = store_at + sizeof(uint32_t);
	if (new_store >= (SCTP_SIGNATURE_SIZE - 3)) {
		new_store = 0;
	}
	if (!atomic_cmpset_int(&inp->store_at, store_at, new_store)) {
		goto retry;
	}
	if (new_store == 0) {
		/* Refill the random store */
		sctp_fill_random_store(inp);
	}
	p = &inp->random_store[store_at];
	xp = (uint32_t *)p;
	x = *xp;
	return (x);
}