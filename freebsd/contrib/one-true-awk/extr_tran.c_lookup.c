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
struct TYPE_6__ {TYPE_1__** tab; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  nval; struct TYPE_5__* cnext; } ;
typedef  TYPE_1__ Cell ;
typedef  TYPE_2__ Array ;

/* Variables and functions */
 int hash (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

Cell *lookup(const char *s, Array *tp)	/* look for s in tp */
{
	Cell *p;
	int h;

	h = hash(s, tp->size);
	for (p = tp->tab[h]; p != NULL; p = p->cnext)
		if (strcmp(s, p->nval) == 0)
			return(p);	/* found it */
	return(NULL);			/* not found */
}