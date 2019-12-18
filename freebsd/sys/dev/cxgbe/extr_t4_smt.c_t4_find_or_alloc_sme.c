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
struct smt_entry {scalar_t__ state; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  smac; } ;
struct smt_data {size_t smt_size; struct smt_entry* smtab; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 scalar_t__ SMT_STATE_SWITCHING ; 
 scalar_t__ SMT_STATE_UNUSED ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct smt_entry *
t4_find_or_alloc_sme(struct smt_data *s, uint8_t *smac)
{
	struct smt_entry *end, *e;
	struct smt_entry *first_free = NULL;

	rw_assert(&s->lock, RA_WLOCKED);
	for (e = &s->smtab[0], end = &s->smtab[s->smt_size]; e != end; ++e) {
		if (atomic_load_acq_int(&e->refcnt) == 0) {
			if (!first_free)
				first_free = e;
		} else {
			if (e->state == SMT_STATE_SWITCHING) {
				/*
				 * This entry is actually in use. See if we can
				 * re-use it?
				 */
				if (memcmp(e->smac, smac, ETHER_ADDR_LEN) == 0)
					goto found_reuse;
			}
		}
	}
	if (first_free) {
		e = first_free;
		goto found;
	}
	return NULL;

found:
	e->state = SMT_STATE_UNUSED;
found_reuse:
	atomic_add_int(&e->refcnt, 1);
	return e;
}