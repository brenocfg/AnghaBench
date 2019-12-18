#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; TYPE_1__** tab; } ;
struct TYPE_5__ {struct TYPE_5__* cnext; int /*<<< orphan*/  nval; } ;
typedef  TYPE_1__ Cell ;
typedef  TYPE_2__ Array ;

/* Variables and functions */
 int GROWTAB ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int hash (int /*<<< orphan*/ ,int) ; 

void rehash(Array *tp)	/* rehash items in small table into big one */
{
	int i, nh, nsz;
	Cell *cp, *op, **np;

	nsz = GROWTAB * tp->size;
	np = (Cell **) calloc(nsz, sizeof(Cell *));
	if (np == NULL)		/* can't do it, but can keep running. */
		return;		/* someone else will run out later. */
	for (i = 0; i < tp->size; i++) {
		for (cp = tp->tab[i]; cp; cp = op) {
			op = cp->cnext;
			nh = hash(cp->nval, nsz);
			cp->cnext = np[nh];
			np[nh] = cp;
		}
	}
	free(tp->tab);
	tp->tab = np;
	tp->size = nsz;
}