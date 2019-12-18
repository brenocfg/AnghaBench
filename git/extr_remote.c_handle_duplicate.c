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
struct ref {scalar_t__ fetch_head_status; struct ref* peer_ref; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ FETCH_HEAD_IGNORE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_duplicate(struct ref *ref1, struct ref *ref2)
{
	if (strcmp(ref1->name, ref2->name)) {
		if (ref1->fetch_head_status != FETCH_HEAD_IGNORE &&
		    ref2->fetch_head_status != FETCH_HEAD_IGNORE) {
			die(_("Cannot fetch both %s and %s to %s"),
			    ref1->name, ref2->name, ref2->peer_ref->name);
		} else if (ref1->fetch_head_status != FETCH_HEAD_IGNORE &&
			   ref2->fetch_head_status == FETCH_HEAD_IGNORE) {
			warning(_("%s usually tracks %s, not %s"),
				ref2->peer_ref->name, ref2->name, ref1->name);
		} else if (ref1->fetch_head_status == FETCH_HEAD_IGNORE &&
			   ref2->fetch_head_status == FETCH_HEAD_IGNORE) {
			die(_("%s tracks both %s and %s"),
			    ref2->peer_ref->name, ref1->name, ref2->name);
		} else {
			/*
			 * This last possibility doesn't occur because
			 * FETCH_HEAD_IGNORE entries always appear at
			 * the end of the list.
			 */
			BUG("Internal error");
		}
	}
	free(ref2->peer_ref);
	free(ref2);
}