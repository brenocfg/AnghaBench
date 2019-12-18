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
struct parse {scalar_t__ error; int slen; int ssize; int /*<<< orphan*/ * strip; } ;
typedef  int /*<<< orphan*/  sop ;

/* Variables and functions */
 int OPSHIFT ; 
 int /*<<< orphan*/  SOP (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enlarge (struct parse*,int) ; 

__attribute__((used)) static void
doemit(struct parse *p, sop op, size_t opnd)
{
	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	/* deal with oversize operands ("can't happen", more or less) */
	assert(opnd < 1<<OPSHIFT);

	/* deal with undersized strip */
	if (p->slen >= p->ssize)
		enlarge(p, (p->ssize+1) / 2 * 3);	/* +50% */
	assert(p->slen < p->ssize);

	/* finally, it's all reduced to the easy case */
	p->strip[p->slen++] = SOP(op, opnd);
}