#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
struct parse {scalar_t__ next; scalar_t__ end; scalar_t__ error; TYPE_1__* g; } ;
struct TYPE_9__ {int icase; int invert; int* bmp; } ;
typedef  TYPE_2__ cset ;
struct TYPE_8__ {int cflags; TYPE_2__* sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHadd (struct parse*,TYPE_2__*,char) ; 
 scalar_t__ EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  MUSTEAT (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXTn (int) ; 
 int /*<<< orphan*/  OANYOF ; 
 int /*<<< orphan*/  OBOW ; 
 int /*<<< orphan*/  OEOW ; 
 int /*<<< orphan*/  OUT ; 
 char PEEK () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  SEETWO (char,char) ; 
 TYPE_2__* allocset (struct parse*) ; 
 int /*<<< orphan*/  freeset (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  ordinary (struct parse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_b_term (struct parse*,TYPE_2__*) ; 
 int /*<<< orphan*/  singleton (TYPE_2__*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void
p_bracket(struct parse *p)
{
	cset *cs;
	wint_t ch;

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

	if ((cs = allocset(p)) == NULL)
		return;

	if (p->g->cflags&REG_ICASE)
		cs->icase = 1;
	if (EAT('^'))
		cs->invert = 1;
	if (EAT(']'))
		CHadd(p, cs, ']');
	else if (EAT('-'))
		CHadd(p, cs, '-');
	while (MORE() && PEEK() != ']' && !SEETWO('-', ']'))
		p_b_term(p, cs);
	if (EAT('-'))
		CHadd(p, cs, '-');
	(void)MUSTEAT(']', REG_EBRACK);

	if (p->error != 0)	/* don't mess things up further */
		return;

	if (cs->invert && p->g->cflags&REG_NEWLINE)
		cs->bmp['\n' >> 3] |= 1 << ('\n' & 7);

	if ((ch = singleton(cs)) != OUT) {	/* optimize singleton sets */
		ordinary(p, ch);
		freeset(p, cs);
	} else
		EMIT(OANYOF, (int)(cs - p->g->sets));
}