#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct termp {scalar_t__ type; TYPE_1__* ps; } ;
struct TYPE_6__ {TYPE_2__* gly; } ;
struct TYPE_5__ {scalar_t__ wx; } ;
struct TYPE_4__ {int flags; int pages; int pdfbody; size_t pscol; size_t psrow; scalar_t__ lastrow; scalar_t__ lastf; int /*<<< orphan*/  scale; int /*<<< orphan*/  pdfbytes; int /*<<< orphan*/  pdflastpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFM2PNT (struct termp*,size_t) ; 
 int MAXCHAR ; 
 int PS_INLINE ; 
 int PS_NEWPAGE ; 
 scalar_t__ TERMTYPE_PS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* fonts ; 
 int /*<<< orphan*/  pdf_obj (struct termp*,int) ; 
 int /*<<< orphan*/  ps_printf (struct termp*,char*,...) ; 
 int /*<<< orphan*/  ps_putchar (struct termp*,char) ; 

__attribute__((used)) static void
ps_pletter(struct termp *p, int c)
{
	int		 f;

	/*
	 * If we haven't opened a page context, then output that we're
	 * in a new page and make sure the font is correctly set.
	 */

	if (PS_NEWPAGE & p->ps->flags) {
		if (TERMTYPE_PS == p->type) {
			ps_printf(p, "%%%%Page: %zu %zu\n",
			    p->ps->pages + 1, p->ps->pages + 1);
			ps_printf(p, "f%d\n", (int)p->ps->lastf);
		} else {
			pdf_obj(p, p->ps->pdfbody +
			    p->ps->pages * 4);
			ps_printf(p, "<<\n");
			ps_printf(p, "/Length %zu 0 R\n",
			    p->ps->pdfbody + 1 + p->ps->pages * 4);
			ps_printf(p, ">>\nstream\n");
		}
		p->ps->pdflastpg = p->ps->pdfbytes;
		p->ps->flags &= ~PS_NEWPAGE;
	}

	/*
	 * If we're not in a PostScript "word" context, then open one
	 * now at the current cursor.
	 */

	if ( ! (PS_INLINE & p->ps->flags)) {
		if (TERMTYPE_PS != p->type) {
			ps_printf(p, "BT\n/F%d %zu Tf\n",
			    (int)p->ps->lastf, p->ps->scale);
			ps_printf(p, "%.3f %.3f Td\n(",
			    AFM2PNT(p, p->ps->pscol),
			    AFM2PNT(p, p->ps->psrow));
		} else {
			ps_printf(p, "%.3f", AFM2PNT(p, p->ps->pscol));
			if (p->ps->psrow != p->ps->lastrow)
				ps_printf(p, " %.3f",
				    AFM2PNT(p, p->ps->psrow));
			ps_printf(p, "(");
		}
		p->ps->flags |= PS_INLINE;
	}

	assert( ! (PS_NEWPAGE & p->ps->flags));

	/*
	 * We need to escape these characters as per the PostScript
	 * specification.  We would also escape non-graphable characters
	 * (like tabs), but none of them would get to this point and
	 * it's superfluous to abort() on them.
	 */

	switch (c) {
	case '(':
	case ')':
	case '\\':
		ps_putchar(p, '\\');
		break;
	default:
		break;
	}

	/* Write the character and adjust where we are on the page. */

	f = (int)p->ps->lastf;

	if (c <= 32 || c - 32 >= MAXCHAR)
		c = 32;

	ps_putchar(p, (char)c);
	c -= 32;
	p->ps->pscol += (size_t)fonts[f].gly[c].wx;
}