#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  action ;
struct TYPE_12__ {scalar_t__* rptlines; TYPE_1__* gp; int /*<<< orphan*/  rptlchange; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* scr_msg ) (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t) ;} ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int ARSIZE (char* const*) ; 
 int /*<<< orphan*/  FREE_SPACE (TYPE_2__*,char*,size_t) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SPACE_GOTOC (TYPE_2__*,char*,size_t,int) ; 
 size_t L_YANKED ; 
 int MAXNUM ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  O_REPORT ; 
 scalar_t__ O_VAL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EX_SILENT ; 
 int /*<<< orphan*/  ex_fflush (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* msg_cat (TYPE_2__*,char* const,size_t*) ; 
 size_t snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t) ; 

void
mod_rpt(SCR *sp)
{
	static char * const action[] = {
		"293|added",
		"294|changed",
		"295|deleted",
		"296|joined",
		"297|moved",
		"298|shifted",
		"299|yanked",
	};
	static char * const lines[] = {
		"300|line",
		"301|lines",
	};
	recno_t total;
	u_long rptval;
	int first, cnt;
	size_t blen, len, tlen;
	const char *t;
	char * const *ap;
	char *bp, *p;

	/* Change reports are turned off in batch mode. */
	if (F_ISSET(sp, SC_EX_SILENT))
		return;

	/* Reset changing line number. */
	sp->rptlchange = OOBLNO;

	/*
	 * Don't build a message if not enough changed.
	 *
	 * !!!
	 * And now, a vi clone test.  Historically, vi reported if the number
	 * of changed lines was > than the value, not >=, unless it was a yank
	 * command, which used >=.  No lie.  Furthermore, an action was never
	 * reported for a single line action.  This is consistent for actions
	 * other than yank, but yank didn't report single line actions even if
	 * the report edit option was set to 1.  In addition, setting report to
	 * 0 in the 4BSD historic vi was equivalent to setting it to 1, for an
	 * unknown reason (this bug was fixed in System III/V at some point).
	 * I got complaints, so nvi conforms to System III/V historic practice
	 * except that we report a yank of 1 line if report is set to 1.
	 */
#define	ARSIZE(a)	sizeof(a) / sizeof (*a)
#define	MAXNUM		25
	rptval = O_VAL(sp, O_REPORT);
	for (cnt = 0, total = 0; cnt < ARSIZE(action); ++cnt)
		total += sp->rptlines[cnt];
	if (total == 0)
		return;
	if (total <= rptval && sp->rptlines[L_YANKED] < rptval) {
		for (cnt = 0; cnt < ARSIZE(action); ++cnt)
			sp->rptlines[cnt] = 0;
		return;
	}

	/* Build and display the message. */
	GET_SPACE_GOTOC(sp, bp, blen, sizeof(action) * MAXNUM + 1);
	for (p = bp, first = 1, tlen = 0,
	    ap = action, cnt = 0; cnt < ARSIZE(action); ++ap, ++cnt)
		if (sp->rptlines[cnt] != 0) {
			if (first)
				first = 0;
			else {
				*p++ = ';';
				*p++ = ' ';
				tlen += 2;
			}
			len = snprintf(p, MAXNUM, "%lu ",
			    (u_long)sp->rptlines[cnt]);
			p += len;
			tlen += len;
			t = msg_cat(sp,
			    lines[sp->rptlines[cnt] == 1 ? 0 : 1], &len);
			memcpy(p, t, len);
			p += len;
			tlen += len;
			*p++ = ' ';
			++tlen;
			t = msg_cat(sp, *ap, &len);
			memcpy(p, t, len);
			p += len;
			tlen += len;
			sp->rptlines[cnt] = 0;
		}

	/* Add trailing newline. */
	*p = '\n';
	++tlen;

	(void)ex_fflush(sp);
	sp->gp->scr_msg(sp, M_INFO, bp, tlen);

	FREE_SPACE(sp, bp, blen);
alloc_err:
	return;

#undef ARSIZE
#undef MAXNUM
}