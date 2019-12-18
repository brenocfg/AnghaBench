#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int recno_t ;
struct TYPE_22__ {int /*<<< orphan*/  ibp; int /*<<< orphan*/  ibcw; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* scr_busy ) (TYPE_1__*,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int lno; } ;
struct TYPE_19__ {TYPE_3__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ MARK ;
typedef  TYPE_3__ GS ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_4__ EX_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_OFF ; 
 int /*<<< orphan*/  BUSY_ON ; 
 int /*<<< orphan*/  BUSY_UPDATE ; 
 TYPE_4__* EXP (TYPE_1__*) ; 
 int /*<<< orphan*/  FILE2INT5 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  FREE_SPACE (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ INTERRUPTED (TYPE_1__*) ; 
 int INTERRUPT_CHECK ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ db_append (TYPE_1__*,int,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ex_getline (TYPE_1__*,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* msg_print (TYPE_1__*,char*,int*) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msgq_str (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

int
ex_readfp(SCR *sp, char *name, FILE *fp, MARK *fm, recno_t *nlinesp, int silent)
{
	EX_PRIVATE *exp;
	GS *gp;
	recno_t lcnt, lno;
	size_t len;
	u_long ccnt;			/* XXX: can't print off_t portably. */
	int nf, rval;
	char *p;
	size_t wlen;
	CHAR_T *wp;

	gp = sp->gp;
	exp = EXP(sp);

	/*
	 * Add in the lines from the output.  Insertion starts at the line
	 * following the address.
	 */
	ccnt = 0;
	lcnt = 0;
	p = "147|Reading...";
	for (lno = fm->lno; !ex_getline(sp, fp, &len); ++lno, ++lcnt) {
		if ((lcnt + 1) % INTERRUPT_CHECK == 0) {
			if (INTERRUPTED(sp))
				break;
			if (!silent) {
				gp->scr_busy(sp, p,
				    p == NULL ? BUSY_UPDATE : BUSY_ON);
				p = NULL;
			}
		}
		FILE2INT5(sp, exp->ibcw, exp->ibp, len, wp, wlen);
		if (db_append(sp, 1, lno, wp, wlen))
			goto err;
		ccnt += len;
	}

	if (ferror(fp) || fclose(fp))
		goto err;

	/* Return the number of lines read in. */
	if (nlinesp != NULL)
		*nlinesp = lcnt;

	if (!silent) {
		p = msg_print(sp, name, &nf);
		msgq(sp, M_INFO,
		    "148|%s: %lu lines, %lu characters", p,
		    (u_long)lcnt, ccnt);
		if (nf)
			FREE_SPACE(sp, p, 0);
	}

	rval = 0;
	if (0) {
err:		msgq_str(sp, M_SYSERR, name, "%s");
		(void)fclose(fp);
		rval = 1;
	}

	if (!silent)
		gp->scr_busy(sp, NULL, BUSY_OFF);
	return (rval);
}