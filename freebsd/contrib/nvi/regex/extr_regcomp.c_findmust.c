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
struct re_guts {int* strip; scalar_t__ mlen; int /*<<< orphan*/ * must; int /*<<< orphan*/  iflags; int /*<<< orphan*/ * stripdata; } ;
struct parse {scalar_t__ error; } ;
typedef  scalar_t__ sopno ;
typedef  int sop ;
typedef  int /*<<< orphan*/  RCHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BAD ; 
#define  OCHAR 133 
#define  OCH_ 132 
 int OEND ; 
#define  OLPAREN 131 
 int OOR2 ; 
#define  OPLUS_ 130 
#define  OQUEST_ 129 
#define  ORPAREN 128 
 int O_CH ; 
 int O_QUEST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static void
findmust(struct parse *p, struct re_guts *g)
{
	sop *scans;
	RCHAR_T *scand;
	sop *starts = 0;
	RCHAR_T *startd = NULL;
	sop *newstarts = 0;
	RCHAR_T *newstartd = NULL;
	sopno newlen;
	sop s;
	RCHAR_T d;
	RCHAR_T *cp;
	sopno i;

	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	/* find the longest OCHAR sequence in strip */
	newlen = 0;
	scans = g->strip + 1;
	scand = g->stripdata + 1;
	do {
		s = *scans++;
		d = *scand++;
		switch (s) {
		case OCHAR:		/* sequence member */
			if (newlen == 0) {		/* new sequence */
				newstarts = scans - 1;
				newstartd = scand - 1;
			}
			newlen++;
			break;
		case OPLUS_:		/* things that don't break one */
		case OLPAREN:
		case ORPAREN:
			break;
		case OQUEST_:		/* things that must be skipped */
		case OCH_:
			scans--;
			scand--;
			do {
				scans += d;
				scand += d;
				s = *scans;
				d = *scand;
				/* assert() interferes w debug printouts */
				if (s != O_QUEST && s != O_CH && s != OOR2) {
					g->iflags |= BAD;
					return;
				}
			} while (s != O_QUEST && s != O_CH);
			/* fallthrough */
		default:		/* things that break a sequence */
			if (newlen > g->mlen) {		/* ends one */
				starts = newstarts;
				startd = newstartd;
				g->mlen = newlen;
			}
			newlen = 0;
			break;
		}
	} while (s != OEND);

	if (g->mlen == 0)		/* there isn't one */
		return;

	/* turn it into a character string */
	g->must = malloc(((size_t)g->mlen + 1) * sizeof(RCHAR_T));
	if (g->must == NULL) {		/* argh; just forget it */
		g->mlen = 0;
		return;
	}
	cp = g->must;
	scans = starts;
	scand = startd;
	for (i = g->mlen; i > 0; i--) {
		for (;;) {
			s = *scans++;
			d = *scand++;
			if (s == OCHAR)
				break;
		}
		assert(cp < g->must + g->mlen);
		*cp++ = d;
	}
	assert(cp == g->must + g->mlen);
	*cp++ = '\0';		/* just on general principles */
}