#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; scalar_t__* ref; } ;
typedef  TYPE_1__ subst_t ;
typedef  int /*<<< orphan*/  srch ;

/* Variables and functions */
 int COLLATE_SUBST_PRIORITY ; 
 int /*<<< orphan*/  INTERR ; 
 TYPE_1__* RB_FIND (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RESOLVED ; 
 int /*<<< orphan*/  add_order_pri (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int curr_subst ; 
 size_t curr_weight ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_pri () ; 
 int* nextsubst ; 
 int /*<<< orphan*/  set_pri (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__* subst_weights ; 
 int /*<<< orphan*/ * substs ; 
 int /*<<< orphan*/ * substs_ref ; 

void
add_order_subst(void)
{
	subst_t srch;
	subst_t	*s;
	int i;

	(void) memset(&srch, 0, sizeof (srch));
	for (i = 0; i < curr_subst; i++) {
		srch.ref[i] = subst_weights[i];
		subst_weights[i] = 0;
	}
	s = RB_FIND(substs_ref, &substs_ref[curr_weight], &srch);

	if (s == NULL) {
		if ((s = calloc(1, sizeof(*s))) == NULL) {
			fprintf(stderr,"out of memory");
			return;
		}
		s->key = new_pri();

		/*
		 * We use a self reference for our key, but we set a
		 * high bit to indicate that this is a substitution
		 * reference.  This will expedite table lookups later,
		 * and prevent table lookups for situations that don't
		 * require it.  (In short, its a big win, because we
		 * can skip a lot of binary searching.)
		 */
		set_pri(s->key,
		    (nextsubst[curr_weight] | COLLATE_SUBST_PRIORITY),
		    RESOLVED);
		nextsubst[curr_weight] += 1;

		for (i = 0; i < curr_subst; i++) {
			s->ref[i] = srch.ref[i];
		}

		RB_INSERT(substs_ref, &substs_ref[curr_weight], s);

		if (RB_FIND(substs, &substs[curr_weight], s) != NULL) {
			INTERR;
			return;
		}
		RB_INSERT(substs, &substs[curr_weight], s);
	}
	curr_subst = 0;


	/*
	 * We are using the current (unique) priority as a search key
	 * in the substitution table.
	 */
	add_order_pri(s->key);
}