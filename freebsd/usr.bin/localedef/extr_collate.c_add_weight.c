#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pri; } ;
typedef  TYPE_1__ weight_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int COLLATE_SUBST_PRIORITY ; 
 int /*<<< orphan*/ * RB_FIND (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int resolve_pri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * weights ; 

void
add_weight(int32_t ref, int pass)
{
	weight_t srch;
	weight_t *w;

	srch.pri = resolve_pri(ref);

	/* No translation of ignores */
	if (srch.pri == 0)
		return;

	/* Substitution priorities are not weights */
	if (srch.pri & COLLATE_SUBST_PRIORITY)
		return;

	if (RB_FIND(weights, &weights[pass], &srch) != NULL)
		return;

	if ((w = calloc(1, sizeof(*w))) == NULL) {
		fprintf(stderr, "out of memory");
		return;
	}
	w->pri = srch.pri;
	RB_INSERT(weights, &weights[pass], w);
}