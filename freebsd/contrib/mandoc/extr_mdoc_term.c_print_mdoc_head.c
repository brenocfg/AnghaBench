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
struct termp {int flags; int trailspace; int maxrmargin; TYPE_1__* tcol; } ;
struct roff_meta {int /*<<< orphan*/ * msec; int /*<<< orphan*/  title; int /*<<< orphan*/ * arch; int /*<<< orphan*/  vol; } ;
struct TYPE_2__ {size_t offset; size_t rmargin; } ;

/* Variables and functions */
 int TERMP_NOBREAK ; 
 int TERMP_NOSPACE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mandoc_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_flushln (struct termp*) ; 
 size_t term_len (struct termp*,int) ; 
 size_t term_strlen (struct termp*,char*) ; 
 int /*<<< orphan*/  term_word (struct termp*,char*) ; 

__attribute__((used)) static void
print_mdoc_head(struct termp *p, const struct roff_meta *meta)
{
	char			*volume, *title;
	size_t			 vollen, titlen;

	/*
	 * The header is strange.  It has three components, which are
	 * really two with the first duplicated.  It goes like this:
	 *
	 * IDENTIFIER              TITLE                   IDENTIFIER
	 *
	 * The IDENTIFIER is NAME(SECTION), which is the command-name
	 * (if given, or "unknown" if not) followed by the manual page
	 * section.  These are given in `Dt'.  The TITLE is a free-form
	 * string depending on the manual volume.  If not specified, it
	 * switches on the manual section.
	 */

	assert(meta->vol);
	if (NULL == meta->arch)
		volume = mandoc_strdup(meta->vol);
	else
		mandoc_asprintf(&volume, "%s (%s)",
		    meta->vol, meta->arch);
	vollen = term_strlen(p, volume);

	if (NULL == meta->msec)
		title = mandoc_strdup(meta->title);
	else
		mandoc_asprintf(&title, "%s(%s)",
		    meta->title, meta->msec);
	titlen = term_strlen(p, title);

	p->flags |= TERMP_NOBREAK | TERMP_NOSPACE;
	p->trailspace = 1;
	p->tcol->offset = 0;
	p->tcol->rmargin = 2 * (titlen+1) + vollen < p->maxrmargin ?
	    (p->maxrmargin - vollen + term_len(p, 1)) / 2 :
	    vollen < p->maxrmargin ?  p->maxrmargin - vollen : 0;

	term_word(p, title);
	term_flushln(p);

	p->flags |= TERMP_NOSPACE;
	p->tcol->offset = p->tcol->rmargin;
	p->tcol->rmargin = p->tcol->offset + vollen + titlen <
	    p->maxrmargin ? p->maxrmargin - titlen : p->maxrmargin;

	term_word(p, volume);
	term_flushln(p);

	p->flags &= ~TERMP_NOBREAK;
	p->trailspace = 0;
	if (p->tcol->rmargin + titlen <= p->maxrmargin) {
		p->flags |= TERMP_NOSPACE;
		p->tcol->offset = p->tcol->rmargin;
		p->tcol->rmargin = p->maxrmargin;
		term_word(p, title);
		term_flushln(p);
	}

	p->flags &= ~TERMP_NOSPACE;
	p->tcol->offset = 0;
	p->tcol->rmargin = p->maxrmargin;
	free(title);
	free(volume);
}