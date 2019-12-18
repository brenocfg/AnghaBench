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
struct roff {int /*<<< orphan*/ * eqn; int /*<<< orphan*/  eqn_inline; TYPE_1__* last_eqn; } ;
struct buf {char* buf; scalar_t__ sz; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdelim; int /*<<< orphan*/  odelim; } ;

/* Variables and functions */
 int ROFF_CONT ; 
 int ROFF_REPARSE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mandoc_asprintf (char**,char*,char*,char const*,char const*,char const*,char const*,char const*,char*) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
roff_eqndelim(struct roff *r, struct buf *buf, int pos)
{
	char		*cp1, *cp2;
	const char	*bef_pr, *bef_nl, *mac, *aft_nl, *aft_pr;

	/*
	 * Outside equations, look for an opening delimiter.
	 * If we are inside an equation, we already know it is
	 * in-line, or this function wouldn't have been called;
	 * so look for a closing delimiter.
	 */

	cp1 = buf->buf + pos;
	cp2 = strchr(cp1, r->eqn == NULL ?
	    r->last_eqn->odelim : r->last_eqn->cdelim);
	if (cp2 == NULL)
		return ROFF_CONT;

	*cp2++ = '\0';
	bef_pr = bef_nl = aft_nl = aft_pr = "";

	/* Handle preceding text, protecting whitespace. */

	if (*buf->buf != '\0') {
		if (r->eqn == NULL)
			bef_pr = "\\&";
		bef_nl = "\n";
	}

	/*
	 * Prepare replacing the delimiter with an equation macro
	 * and drop leading white space from the equation.
	 */

	if (r->eqn == NULL) {
		while (*cp2 == ' ')
			cp2++;
		mac = ".EQ";
	} else
		mac = ".EN";

	/* Handle following text, protecting whitespace. */

	if (*cp2 != '\0') {
		aft_nl = "\n";
		if (r->eqn != NULL)
			aft_pr = "\\&";
	}

	/* Do the actual replacement. */

	buf->sz = mandoc_asprintf(&cp1, "%s%s%s%s%s%s%s", buf->buf,
	    bef_pr, bef_nl, mac, aft_nl, aft_pr, cp2) + 1;
	free(buf->buf);
	buf->buf = cp1;

	/* Toggle the in-line state of the eqn subsystem. */

	r->eqn_inline = r->eqn == NULL;
	return ROFF_REPARSE;
}