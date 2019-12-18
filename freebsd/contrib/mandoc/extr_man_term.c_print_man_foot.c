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
struct termp {int flags; int trailspace; size_t maxrmargin; TYPE_1__* tcol; int /*<<< orphan*/  mdocstyle; } ;
struct roff_meta {char* title; char* msec; char* date; char* os; scalar_t__ hasbody; } ;
struct TYPE_2__ {size_t offset; size_t rmargin; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERMFONT_NONE ; 
 int TERMP_NOBREAK ; 
 int TERMP_NOSPACE ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char*,char*) ; 
 char* mandoc_strdup (char*) ; 
 int /*<<< orphan*/  term_flushln (struct termp*) ; 
 int /*<<< orphan*/  term_fontrepl (struct termp*,int /*<<< orphan*/ ) ; 
 size_t term_len (struct termp*,int) ; 
 size_t term_strlen (struct termp*,char*) ; 
 int /*<<< orphan*/  term_vspace (struct termp*) ; 
 int /*<<< orphan*/  term_word (struct termp*,char*) ; 

__attribute__((used)) static void
print_man_foot(struct termp *p, const struct roff_meta *meta)
{
	char			*title;
	size_t			 datelen, titlen;

	assert(meta->title);
	assert(meta->msec);
	assert(meta->date);

	term_fontrepl(p, TERMFONT_NONE);

	if (meta->hasbody)
		term_vspace(p);

	/*
	 * Temporary, undocumented option to imitate mdoc(7) output.
	 * In the bottom right corner, use the operating system
	 * instead of the title.
	 */

	if ( ! p->mdocstyle) {
		if (meta->hasbody) {
			term_vspace(p);
			term_vspace(p);
		}
		mandoc_asprintf(&title, "%s(%s)",
		    meta->title, meta->msec);
	} else if (meta->os != NULL) {
		title = mandoc_strdup(meta->os);
	} else {
		title = mandoc_strdup("");
	}
	datelen = term_strlen(p, meta->date);

	/* Bottom left corner: operating system. */

	p->flags |= TERMP_NOSPACE | TERMP_NOBREAK;
	p->trailspace = 1;
	p->tcol->offset = 0;
	p->tcol->rmargin = p->maxrmargin > datelen ?
	    (p->maxrmargin + term_len(p, 1) - datelen) / 2 : 0;

	if (meta->os)
		term_word(p, meta->os);
	term_flushln(p);

	/* At the bottom in the middle: manual date. */

	p->tcol->offset = p->tcol->rmargin;
	titlen = term_strlen(p, title);
	p->tcol->rmargin = p->maxrmargin > titlen ?
	    p->maxrmargin - titlen : 0;
	p->flags |= TERMP_NOSPACE;

	term_word(p, meta->date);
	term_flushln(p);

	/* Bottom right corner: manual title and section. */

	p->flags &= ~TERMP_NOBREAK;
	p->flags |= TERMP_NOSPACE;
	p->trailspace = 0;
	p->tcol->offset = p->tcol->rmargin;
	p->tcol->rmargin = p->maxrmargin;

	term_word(p, title);
	term_flushln(p);

	/*
	 * Reset the terminal state for more output after the footer:
	 * Some output modes, in particular PostScript and PDF, print
	 * the header and the footer into a buffer such that it can be
	 * reused for multiple output pages, then go on to format the
	 * main text.
	 */

        p->tcol->offset = 0;
        p->flags = 0;

	free(title);
}