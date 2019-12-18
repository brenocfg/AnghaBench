#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parse {TYPE_1__* g; } ;
typedef  int /*<<< orphan*/  cset ;
struct TYPE_2__ {size_t ncsets; int /*<<< orphan*/  csetsize; int /*<<< orphan*/ * sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHsub (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
freeset(struct parse *p, cset *cs)
{
	size_t i;
	cset *top = &p->g->sets[p->g->ncsets];
	size_t css = (size_t)p->g->csetsize;

	for (i = 0; i < css; i++)
		CHsub(cs, i);
	if (cs == top-1)	/* recover only the easy case */
		p->g->ncsets--;
}