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
struct tp_entry {scalar_t__ sysindex; int /*<<< orphan*/  tp_addr; } ;
struct tp_entries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct tp_entry*,struct tp_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct tp_entries*,struct tp_entry*,int /*<<< orphan*/ ) ; 
 struct tp_entry* TAILQ_NEXT (struct tp_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ bridge_compare_macs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_e ; 

__attribute__((used)) static void
bridge_addrs_insert_at(struct tp_entries *headp,
	struct tp_entry *ta, struct tp_entry **f_tpa)
{
	struct tp_entry *t1;

	assert(f_tpa != NULL);

	for (t1 = *f_tpa;
	    t1 != NULL && ta->sysindex == t1->sysindex;
	    t1 = TAILQ_NEXT(t1, tp_e)) {
		if (bridge_compare_macs(ta->tp_addr, t1->tp_addr) < 0) {
			TAILQ_INSERT_BEFORE(t1, ta, tp_e);
			if (*f_tpa == t1)
				(*f_tpa) = ta;
			return;
		}
	}

	if (t1 == NULL)
		TAILQ_INSERT_TAIL(headp, ta, tp_e);
	else
		TAILQ_INSERT_BEFORE(t1, ta, tp_e);
}