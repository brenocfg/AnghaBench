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
struct termp {TYPE_1__* ps; } ;
struct TYPE_2__ {char last; int flags; int nextf; size_t pscol; size_t pscolnext; } ;

/* Variables and functions */
 int PS_BACKSP ; 
 size_t SIZE_MAX ; 
#define  TERMFONT_BI 130 
#define  TERMFONT_BOLD 129 
#define  TERMFONT_UNDER 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ps_pclose (struct termp*) ; 
 int /*<<< orphan*/  ps_plast (struct termp*) ; 

__attribute__((used)) static void
ps_letter(struct termp *p, int arg)
{
	size_t		savecol;
	char		c;

	c = arg >= 128 || arg <= 0 ? '?' : arg;

	/*
	 * When receiving a backspace, merely flag it.
	 * We don't know yet whether it is
	 * a font instruction or an overstrike.
	 */

	if (c == '\b') {
		assert(p->ps->last != '\0');
		assert( ! (p->ps->flags & PS_BACKSP));
		p->ps->flags |= PS_BACKSP;
		return;
	}

	/*
	 * Decode font instructions.
	 */

	if (p->ps->flags & PS_BACKSP) {
		if (p->ps->last == '_') {
			switch (p->ps->nextf) {
			case TERMFONT_BI:
				break;
			case TERMFONT_BOLD:
				p->ps->nextf = TERMFONT_BI;
				break;
			default:
				p->ps->nextf = TERMFONT_UNDER;
			}
			p->ps->last = c;
			p->ps->flags &= ~PS_BACKSP;
			return;
		}
		if (p->ps->last == c) {
			switch (p->ps->nextf) {
			case TERMFONT_BI:
				break;
			case TERMFONT_UNDER:
				p->ps->nextf = TERMFONT_BI;
				break;
			default:
				p->ps->nextf = TERMFONT_BOLD;
			}
			p->ps->flags &= ~PS_BACKSP;
			return;
		}

		/*
		 * This is not a font instruction, but rather
		 * the next character.  Prepare for overstrike.
		 */

		savecol = p->ps->pscol;
	} else
		savecol = SIZE_MAX;

	/*
	 * We found the next character, so the font instructions
	 * for the previous one are complete.
	 * Use them and print it.
	 */

	ps_plast(p);

	/*
	 * Do not print the current character yet because font
	 * instructions might follow; only remember the character.
	 * It will get printed later from ps_plast().
	 */

	p->ps->last = c;

	/*
	 * For an overstrike, back up to the previous position.
	 * If the previous character is wider than any it overstrikes,
	 * remember the current position, because it might also be
	 * wider than all that will overstrike it.
	 */

	if (savecol != SIZE_MAX) {
		if (p->ps->pscolnext < p->ps->pscol)
			p->ps->pscolnext = p->ps->pscol;
		ps_pclose(p);
		p->ps->pscol = savecol;
		p->ps->flags &= ~PS_BACKSP;
	} else
		p->ps->pscolnext = 0;
}