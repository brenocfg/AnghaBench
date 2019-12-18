#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct parse {scalar_t__ next; scalar_t__ end; scalar_t__ error; TYPE_1__* g; } ;
struct TYPE_15__ {int /*<<< orphan*/ * multis; } ;
typedef  TYPE_2__ cset ;
struct TYPE_14__ {int cflags; int csetsize; } ;

/* Variables and functions */
 scalar_t__ CHIN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  CHadd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  CHsub (TYPE_2__*,char) ; 
 scalar_t__ EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  MUSTEAT (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXTn (int) ; 
 int /*<<< orphan*/  OANYOF ; 
 int /*<<< orphan*/  OBOW ; 
 int /*<<< orphan*/  OEOW ; 
 char PEEK () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  SEETWO (char,char) ; 
 TYPE_2__* allocset (struct parse*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstch (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  freeset (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  freezeset (struct parse*,TYPE_2__*) ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  mccase (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  mcinvert (struct parse*,TYPE_2__*) ; 
 int nch (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  ordinary (struct parse*,int /*<<< orphan*/ ) ; 
 int othercase (int) ; 
 int /*<<< orphan*/  p_b_term (struct parse*,TYPE_2__*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void
p_bracket(struct parse *p)
{
	cset *cs;
	int invert = 0;

	/* Dept of Truly Sickening Special-Case Kludges */
	if (p->next + 5 < p->end && strncmp(p->next, "[:<:]]", 6) == 0) {
		EMIT(OBOW, 0);
		NEXTn(6);
		return;
	}
	if (p->next + 5 < p->end && strncmp(p->next, "[:>:]]", 6) == 0) {
		EMIT(OEOW, 0);
		NEXTn(6);
		return;
	}

	if ((cs = allocset(p)) == NULL) {
		/* allocset did set error status in p */
		return;
	}

	if (EAT('^'))
		invert++;	/* make note to invert set at end */
	if (EAT(']'))
		CHadd(cs, ']');
	else if (EAT('-'))
		CHadd(cs, '-');
	while (MORE() && PEEK() != ']' && !SEETWO('-', ']'))
		p_b_term(p, cs);
	if (EAT('-'))
		CHadd(cs, '-');
	MUSTEAT(']', REG_EBRACK);

	if (p->error != 0) {	/* don't mess things up further */
		freeset(p, cs);
		return;
	}

	if (p->g->cflags&REG_ICASE) {
		int i;
		int ci;

		for (i = p->g->csetsize - 1; i >= 0; i--)
			if (CHIN(cs, i) && isalpha(i)) {
				ci = othercase(i);
				if (ci != i)
					CHadd(cs, ci);
			}
		if (cs->multis != NULL)
			mccase(p, cs);
	}
	if (invert) {
		int i;

		for (i = p->g->csetsize - 1; i >= 0; i--)
			if (CHIN(cs, i))
				CHsub(cs, i);
			else
				CHadd(cs, i);
		if (p->g->cflags&REG_NEWLINE)
			CHsub(cs, '\n');
		if (cs->multis != NULL)
			mcinvert(p, cs);
	}

	assert(cs->multis == NULL);		/* xxx */

	if (nch(p, cs) == 1) {		/* optimize singleton sets */
		ordinary(p, firstch(p, cs));
		freeset(p, cs);
	} else
		EMIT(OANYOF, freezeset(p, cs));
}