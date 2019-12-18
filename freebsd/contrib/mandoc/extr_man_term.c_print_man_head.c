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
struct termp {int flags; int trailspace; int maxrmargin; int /*<<< orphan*/  mdocstyle; TYPE_1__* tcol; } ;
struct roff_meta {char* vol; int /*<<< orphan*/  msec; int /*<<< orphan*/  title; } ;
struct TYPE_2__ {size_t offset; size_t rmargin; } ;

/* Variables and functions */
 int TERMP_NOBREAK ; 
 int TERMP_NOSPACE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_flushln (struct termp*) ; 
 size_t term_len (struct termp*,int) ; 
 size_t term_strlen (struct termp*,char const*) ; 
 int /*<<< orphan*/  term_vspace (struct termp*) ; 
 int /*<<< orphan*/  term_word (struct termp*,char const*) ; 

__attribute__((used)) static void
print_man_head(struct termp *p, const struct roff_meta *meta)
{
	const char		*volume;
	char			*title;
	size_t			 vollen, titlen;

	assert(meta->title);
	assert(meta->msec);

	volume = NULL == meta->vol ? "" : meta->vol;
	vollen = term_strlen(p, volume);

	/* Top left corner: manual title and section. */

	mandoc_asprintf(&title, "%s(%s)", meta->title, meta->msec);
	titlen = term_strlen(p, title);

	p->flags |= TERMP_NOBREAK | TERMP_NOSPACE;
	p->trailspace = 1;
	p->tcol->offset = 0;
	p->tcol->rmargin = 2 * (titlen+1) + vollen < p->maxrmargin ?
	    (p->maxrmargin - vollen + term_len(p, 1)) / 2 :
	    vollen < p->maxrmargin ? p->maxrmargin - vollen : 0;

	term_word(p, title);
	term_flushln(p);

	/* At the top in the middle: manual volume. */

	p->flags |= TERMP_NOSPACE;
	p->tcol->offset = p->tcol->rmargin;
	p->tcol->rmargin = p->tcol->offset + vollen + titlen <
	    p->maxrmargin ?  p->maxrmargin - titlen : p->maxrmargin;

	term_word(p, volume);
	term_flushln(p);

	/* Top right corner: title and section, again. */

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

	/*
	 * Groff prints three blank lines before the content.
	 * Do the same, except in the temporary, undocumented
	 * mode imitating mdoc(7) output.
	 */

	term_vspace(p);
	if ( ! p->mdocstyle) {
		term_vspace(p);
		term_vspace(p);
	}
	free(title);
}