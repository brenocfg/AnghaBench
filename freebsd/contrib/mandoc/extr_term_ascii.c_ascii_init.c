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
struct termp {int maxtcol; int line; int defrmargin; int lastrmargin; int fontsz; int enc; int mdocstyle; int defindent; int synopsisonly; int /*<<< orphan*/  width; int /*<<< orphan*/  letter; int /*<<< orphan*/  endline; int /*<<< orphan*/  advance; int /*<<< orphan*/  setwidth; int /*<<< orphan*/  type; int /*<<< orphan*/  hspan; int /*<<< orphan*/  end; int /*<<< orphan*/  begin; int /*<<< orphan*/  fontl; int /*<<< orphan*/ * fontq; void* tcols; void* tcol; } ;
struct manoutput {int indent; int width; scalar_t__ synopsisonly; scalar_t__ mdoc; } ;
typedef  enum termenc { ____Placeholder_termenc } termenc ;

/* Variables and functions */
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int MB_CUR_MAX ; 
 int TERMENC_ASCII ; 
 int TERMENC_LOCALE ; 
 int TERMENC_UTF8 ; 
 int /*<<< orphan*/  TERMFONT_NONE ; 
 int /*<<< orphan*/  TERMTYPE_CHAR ; 
 int UINT16_MAX ; 
 char* UTF8_LOCALE ; 
 int /*<<< orphan*/  ascii_advance ; 
 int /*<<< orphan*/  ascii_begin ; 
 int /*<<< orphan*/  ascii_end ; 
 int /*<<< orphan*/  ascii_endline ; 
 int /*<<< orphan*/  ascii_hspan ; 
 int /*<<< orphan*/  ascii_letter ; 
 int /*<<< orphan*/  ascii_setwidth ; 
 int /*<<< orphan*/  ascii_width ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  locale_advance ; 
 int /*<<< orphan*/  locale_endline ; 
 int /*<<< orphan*/  locale_letter ; 
 int /*<<< orphan*/  locale_width ; 
 void* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/ * mandoc_reallocarray (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct termp *
ascii_init(enum termenc enc, const struct manoutput *outopts)
{
#if HAVE_WCHAR
	char		*v;
#endif
	struct termp	*p;

	p = mandoc_calloc(1, sizeof(*p));
	p->tcol = p->tcols = mandoc_calloc(1, sizeof(*p->tcol));
	p->maxtcol = 1;

	p->line = 1;
	p->defrmargin = p->lastrmargin = 78;
	p->fontq = mandoc_reallocarray(NULL,
	     (p->fontsz = 8), sizeof(*p->fontq));
	p->fontq[0] = p->fontl = TERMFONT_NONE;

	p->begin = ascii_begin;
	p->end = ascii_end;
	p->hspan = ascii_hspan;
	p->type = TERMTYPE_CHAR;

	p->enc = TERMENC_ASCII;
	p->advance = ascii_advance;
	p->endline = ascii_endline;
	p->letter = ascii_letter;
	p->setwidth = ascii_setwidth;
	p->width = ascii_width;

#if HAVE_WCHAR
	if (enc != TERMENC_ASCII) {

		/*
		 * Do not change any of this to LC_ALL.  It might break
		 * the formatting by subtly changing the behaviour of
		 * various functions, for example strftime(3).  As a
		 * worst case, it might even cause buffer overflows.
		 */

		v = enc == TERMENC_LOCALE ?
		    setlocale(LC_CTYPE, "") :
		    setlocale(LC_CTYPE, UTF8_LOCALE);

		/*
		 * We only support UTF-8,
		 * so revert to ASCII for anything else.
		 */

		if (v != NULL &&
		    strcmp(nl_langinfo(CODESET), "UTF-8") != 0)
			v = setlocale(LC_CTYPE, "C");

		if (v != NULL && MB_CUR_MAX > 1) {
			p->enc = TERMENC_UTF8;
			p->advance = locale_advance;
			p->endline = locale_endline;
			p->letter = locale_letter;
			p->width = locale_width;
		}
	}
#endif

	if (outopts->mdoc) {
		p->mdocstyle = 1;
		p->defindent = 5;
	}
	if (outopts->indent)
		p->defindent = outopts->indent;
	if (outopts->width)
		p->defrmargin = outopts->width;
	if (outopts->synopsisonly)
		p->synopsisonly = 1;

	assert(p->defindent < UINT16_MAX);
	assert(p->defrmargin < UINT16_MAX);
	return p;
}