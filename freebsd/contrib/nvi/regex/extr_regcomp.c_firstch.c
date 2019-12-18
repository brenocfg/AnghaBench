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
struct TYPE_2__ {int /*<<< orphan*/  csetsize; } ;

/* Variables and functions */
 scalar_t__ CHIN (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  never ; 

__attribute__((used)) static int			/* character; there is no "none" value */
firstch(struct parse *p, cset *cs)
{
	size_t i;
	size_t css = (size_t)p->g->csetsize;

	for (i = 0; i < css; i++)
		if (CHIN(cs, i))
			return((char)i);
	assert(never);
	return(0);		/* arbitrary */
}