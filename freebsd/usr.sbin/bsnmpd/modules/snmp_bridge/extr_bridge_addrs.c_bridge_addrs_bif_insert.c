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
struct tp_entry {int /*<<< orphan*/  sysindex; } ;
struct tp_entries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (struct tp_entries*,struct tp_entry*,struct tp_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct tp_entries*,struct tp_entry*,int /*<<< orphan*/ ) ; 
 struct tp_entry* bridge_addrs_find_pos (struct tp_entries*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_addrs_insert_at (struct tp_entries*,struct tp_entry*,struct tp_entry**) ; 
 int /*<<< orphan*/  tp_e ; 

__attribute__((used)) static void
bridge_addrs_bif_insert(struct tp_entries *headp, struct tp_entry *te,
    struct tp_entry **f_tpa)
{
	struct tp_entry *temp;

	if (*f_tpa != NULL)
		bridge_addrs_insert_at(headp, te, f_tpa);
	else {
		temp = bridge_addrs_find_pos(headp, te->sysindex);

		if (temp == NULL)
			TAILQ_INSERT_HEAD(headp, te, tp_e);
		else
			TAILQ_INSERT_AFTER(headp, temp, te, tp_e);
		*f_tpa = te;
	}
}