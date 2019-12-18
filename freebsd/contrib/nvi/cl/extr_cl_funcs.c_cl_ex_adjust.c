#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int exadj_t ;
struct TYPE_3__ {int /*<<< orphan*/ * el; int /*<<< orphan*/ * cup; int /*<<< orphan*/ * cuu1; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_1__* CLP (int /*<<< orphan*/ *) ; 
#define  EX_TERM_CE 129 
#define  EX_TERM_SCROLL 128 
 int /*<<< orphan*/  LINES ; 
 int MAX_CHARACTER_COLUMNS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cl_putchar ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * tgoto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
cl_ex_adjust(SCR *sp, exadj_t action)
{
	CL_PRIVATE *clp;
	int cnt;

	clp = CLP(sp);
	switch (action) {
	case EX_TERM_SCROLL:
		/* Move the cursor up one line if that's possible. */
		if (clp->cuu1 != NULL)
			(void)tputs(clp->cuu1, 1, cl_putchar);
		else if (clp->cup != NULL)
			(void)tputs(tgoto(clp->cup,
			    0, LINES - 2), 1, cl_putchar);
		else
			return (0);
		/* FALLTHROUGH */
	case EX_TERM_CE:
		/* Clear the line. */
		if (clp->el != NULL) {
			(void)putchar('\r');
			(void)tputs(clp->el, 1, cl_putchar);
		} else {
			/*
			 * Historically, ex didn't erase the line, so, if the
			 * displayed line was only a single glyph, and <eof>
			 * was more than one glyph, the output would not fully
			 * overwrite the user's input.  To fix this, output
			 * the maxiumum character number of spaces.  Note,
			 * this won't help if the user entered extra prompt
			 * or <blank> characters before the command character.
			 * We'd have to do a lot of work to make that work, and
			 * it's almost certainly not worth the effort.
			 */
			for (cnt = 0; cnt < MAX_CHARACTER_COLUMNS; ++cnt)
				(void)putchar('\b');
			for (cnt = 0; cnt < MAX_CHARACTER_COLUMNS; ++cnt)
				(void)putchar(' ');
			(void)putchar('\r');
			(void)fflush(stdout);
		}
		break;
	default:
		abort();
	}
	return (0);
}