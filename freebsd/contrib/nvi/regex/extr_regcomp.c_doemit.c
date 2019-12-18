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
struct parse {scalar_t__ error; size_t slen; size_t ssize; size_t* stripdata; int /*<<< orphan*/ * strip; } ;
typedef  int /*<<< orphan*/  sop ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enlarge (struct parse*,int) ; 

__attribute__((used)) static void
doemit(struct parse *p, sop op, size_t opnd)
{
	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	/* deal with oversize operands ("can't happen", more or less) */
	assert(opnd < 1);

	/* deal with undersized strip */
	if (p->slen >= p->ssize)
		if (!enlarge(p, (p->ssize+1) / 2 * 3))	/* +50% */
			return;

	/* finally, it's all reduced to the easy case */
	p->strip[p->slen] = op;
	p->stripdata[p->slen] = opnd;
	p->slen++;
}