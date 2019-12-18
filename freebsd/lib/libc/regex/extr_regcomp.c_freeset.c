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
struct parse {TYPE_1__* g; } ;
struct TYPE_6__ {int /*<<< orphan*/  types; int /*<<< orphan*/  ranges; int /*<<< orphan*/  wides; } ;
typedef  TYPE_2__ cset ;
struct TYPE_5__ {size_t ncsets; TYPE_2__* sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
freeset(struct parse *p, cset *cs)
{
	cset *top = &p->g->sets[p->g->ncsets];

	free(cs->wides);
	free(cs->ranges);
	free(cs->types);
	memset(cs, 0, sizeof(*cs));
	if (cs == top-1)	/* recover only the easy case */
		p->g->ncsets--;
}