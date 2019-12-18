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
typedef  int wint_t ;
struct parse {TYPE_1__* g; } ;
typedef  int /*<<< orphan*/  cset ;
struct TYPE_2__ {int cflags; int /*<<< orphan*/ * sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHadd (struct parse*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OANYOF ; 
 int /*<<< orphan*/  OCHAR ; 
 int OPDMASK ; 
 int REG_ICASE ; 
 int /*<<< orphan*/ * allocset (struct parse*) ; 
 int /*<<< orphan*/  bothcases (struct parse*,int) ; 
 scalar_t__ iswalpha (int) ; 
 int othercase (int) ; 

__attribute__((used)) static void
ordinary(struct parse *p, wint_t ch)
{
	cset *cs;

	if ((p->g->cflags&REG_ICASE) && iswalpha(ch) && othercase(ch) != ch)
		bothcases(p, ch);
	else if ((ch & OPDMASK) == ch)
		EMIT(OCHAR, ch);
	else {
		/*
		 * Kludge: character is too big to fit into an OCHAR operand.
		 * Emit a singleton set.
		 */
		if ((cs = allocset(p)) == NULL)
			return;
		CHadd(p, cs, ch);
		EMIT(OANYOF, (int)(cs - p->g->sets));
	}
}