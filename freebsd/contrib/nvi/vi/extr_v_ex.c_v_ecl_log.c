#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_13__ {scalar_t__ ep; TYPE_1__* gp; } ;
struct TYPE_12__ {size_t len; int /*<<< orphan*/  lb; } ;
struct TYPE_11__ {TYPE_3__* ccl_sp; } ;
typedef  TYPE_2__ TEXT ;
typedef  TYPE_3__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int db_append (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  db_get (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ db_last (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  log_cursor (TYPE_3__*) ; 
 scalar_t__ v_ecl_init (TYPE_3__*) ; 

__attribute__((used)) static int
v_ecl_log(SCR *sp, TEXT *tp)
{
	recno_t lno;
	int rval;
	CHAR_T *p;
	size_t len;
	SCR *ccl_sp;

	/* Initialize the screen, if necessary. */
	if (sp->gp->ccl_sp == NULL && v_ecl_init(sp))
		return (1);

	ccl_sp = sp->gp->ccl_sp;

	/*
	 * Don't log colon command window commands into the colon command
	 * window...
	 */
	if (sp->ep == ccl_sp->ep)
		return (0);

	if (db_last(ccl_sp, &lno)) {
		return (1);
	}
	/* Don't log line that is identical to previous one */
	if (lno > 0 &&
	    !db_get(ccl_sp, lno, 0, &p, &len) &&
	    len == tp->len &&
	    !MEMCMP(tp->lb, p, len))
		rval = 0;
	else {
		rval = db_append(ccl_sp, 0, lno, tp->lb, tp->len);
		/* XXXX end "transaction" on ccl */
		/* Is this still necessary now that we no longer hijack sp ? */
		log_cursor(ccl_sp);
	}

	return (rval);
}