#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {char* symbol; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * expand; } ;
typedef  TYPE_1__ collelem_t ;

/* Variables and functions */
 scalar_t__ COLLATE_STR_LEN ; 
 int COLL_WEIGHTS_MAX ; 
 int /*<<< orphan*/ * RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  elem_by_expand ; 
 int /*<<< orphan*/  elem_by_symbol ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  new_pri () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

void
define_collelem(char *name, wchar_t *wcs)
{
	collelem_t	*e;
	int		i;

	if (wcslen(wcs) >= COLLATE_STR_LEN) {
		fprintf(stderr,"expanded collation element too long");
		return;
	}

	if ((e = calloc(1, sizeof(*e))) == NULL) {
		fprintf(stderr, "out of memory");
		return;
	}
	e->expand = wcs;
	e->symbol = name;

	/*
	 * This is executed before the order statement, so we don't
	 * know how many priorities we *really* need.  We allocate one
	 * for each possible weight.  Not a big deal, as collating-elements
	 * prove to be quite rare.
	 */
	for (i = 0; i < COLL_WEIGHTS_MAX; i++) {
		e->ref[i] = new_pri();
	}

	/* A character sequence can only reduce to one element. */
	if ((RB_FIND(elem_by_symbol, &elem_by_symbol, e) != NULL) ||
	    (RB_FIND(elem_by_expand, &elem_by_expand, e) != NULL)) {
		fprintf(stderr, "duplicate collating element definition");
		free(e);
		return;
	}
	RB_INSERT(elem_by_symbol, &elem_by_symbol, e);
	RB_INSERT(elem_by_expand, &elem_by_expand, e);
}