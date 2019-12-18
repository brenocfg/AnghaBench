#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nelem; TYPE_1__** tab; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {struct TYPE_7__* nval; scalar_t__ sval; struct TYPE_7__* cnext; } ;
typedef  TYPE_1__ Cell ;
typedef  TYPE_2__ Array ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ freeable (TYPE_1__*) ; 
 int hash (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void freeelem(Cell *ap, const char *s)	/* free elem s from ap (i.e., ap["s"] */
{
	Array *tp;
	Cell *p, *prev = NULL;
	int h;
	
	tp = (Array *) ap->sval;
	h = hash(s, tp->size);
	for (p = tp->tab[h]; p != NULL; prev = p, p = p->cnext)
		if (strcmp(s, p->nval) == 0) {
			if (prev == NULL)	/* 1st one */
				tp->tab[h] = p->cnext;
			else			/* middle somewhere */
				prev->cnext = p->cnext;
			if (freeable(p))
				xfree(p->sval);
			free(p->nval);
			free(p);
			tp->nelem--;
			return;
		}
}