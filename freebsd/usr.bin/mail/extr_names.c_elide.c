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
struct name {struct name* n_flink; struct name* n_blink; int /*<<< orphan*/  n_name; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct name *
elide(struct name *names)
{
	struct name *np, *t, *new;
	struct name *x;

	if (names == NULL)
		return (NULL);
	new = names;
	np = names;
	np = np->n_flink;
	if (np != NULL)
		np->n_blink = NULL;
	new->n_flink = NULL;
	while (np != NULL) {
		t = new;
		while (strcasecmp(t->n_name, np->n_name) < 0) {
			if (t->n_flink == NULL)
				break;
			t = t->n_flink;
		}

		/*
		 * If we ran out of t's, put the new entry after
		 * the current value of t.
		 */

		if (strcasecmp(t->n_name, np->n_name) < 0) {
			t->n_flink = np;
			np->n_blink = t;
			t = np;
			np = np->n_flink;
			t->n_flink = NULL;
			continue;
		}

		/*
		 * Otherwise, put the new entry in front of the
		 * current t.  If at the front of the list,
		 * the new guy becomes the new head of the list.
		 */

		if (t == new) {
			t = np;
			np = np->n_flink;
			t->n_flink = new;
			new->n_blink = t;
			t->n_blink = NULL;
			new = t;
			continue;
		}

		/*
		 * The normal case -- we are inserting into the
		 * middle of the list.
		 */

		x = np;
		np = np->n_flink;
		x->n_flink = t;
		x->n_blink = t->n_blink;
		t->n_blink->n_flink = x;
		t->n_blink = x;
	}

	/*
	 * Now the list headed up by new is sorted.
	 * Go through it and remove duplicates.
	 */

	np = new;
	while (np != NULL) {
		t = np;
		while (t->n_flink != NULL &&
		    strcasecmp(np->n_name, t->n_flink->n_name) == 0)
			t = t->n_flink;
		if (t == np || t == NULL) {
			np = np->n_flink;
			continue;
		}

		/*
		 * Now t points to the last entry with the same name
		 * as np.  Make np point beyond t.
		 */

		np->n_flink = t->n_flink;
		if (t->n_flink != NULL)
			t->n_flink->n_blink = np;
		np = np->n_flink;
	}
	return (new);
}