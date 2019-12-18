#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  lno ;
struct TYPE_18__ {int (* seq ) (TYPE_5__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {scalar_t__* data; int size; } ;
struct TYPE_16__ {scalar_t__ c_nlines; scalar_t__ c_lno; scalar_t__* c_lp; size_t c_len; int /*<<< orphan*/  c_blen; TYPE_5__* db; } ;
struct TYPE_15__ {int /*<<< orphan*/  tiq; TYPE_3__* ep; } ;
struct TYPE_14__ {scalar_t__ lno; } ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;
typedef  TYPE_4__ DBT ;
typedef  scalar_t__ CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_GOTOW (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  EXM_NOFILEYET ; 
 int /*<<< orphan*/  FILE2INT (TYPE_2__*,scalar_t__*,int,scalar_t__*,size_t) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCPY (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  R_LAST ; 
 int /*<<< orphan*/  SC_TINPUT ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_LAST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _texth ; 
 int /*<<< orphan*/  ex_emsg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_5__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

int
db_last(
	SCR *sp,
	recno_t *lnop)
{
	DBT data, key;
	EXF *ep;
	recno_t lno;
	CHAR_T *wp;
	size_t wlen;

	/* Check for no underlying file. */
	if ((ep = sp->ep) == NULL) {
		ex_emsg(sp, NULL, EXM_NOFILEYET);
		return (1);
	}
		
	/*
	 * Check the last-line number cache.  Adjust the cached line
	 * number for the lines used by the text input buffers.
	 */
	if (ep->c_nlines != OOBLNO) {
		*lnop = ep->c_nlines;
		if (F_ISSET(sp, SC_TINPUT))
			*lnop += ((TEXT *)TAILQ_LAST(sp->tiq, _texth))->lno -
			    ((TEXT *)TAILQ_FIRST(sp->tiq))->lno;
		return (0);
	}

	key.data = &lno;
	key.size = sizeof(lno);

	switch (ep->db->seq(ep->db, &key, &data, R_LAST)) {
	case -1:
alloc_err:
		msgq(sp, M_SYSERR, "007|unable to get last line");
		*lnop = 0;
		return (1);
	case 1:
		*lnop = 0;
		return (0);
	}

	memcpy(&lno, key.data, sizeof(lno));

	if (lno != ep->c_lno) {
		FILE2INT(sp, data.data, data.size, wp, wlen);

		/* Fill the cache. */
		if (wp != data.data) {
			BINC_GOTOW(sp, ep->c_lp, ep->c_blen, wlen);
			MEMCPY(ep->c_lp, wp, wlen);
		} else
			ep->c_lp = data.data;
		ep->c_lno = lno;
		ep->c_len = wlen;
	}
	ep->c_nlines = lno;

	/* Return the value. */
	*lnop = (F_ISSET(sp, SC_TINPUT) &&
	    ((TEXT *)TAILQ_LAST(sp->tiq, _texth))->lno > lno ?
	    ((TEXT *)TAILQ_LAST(sp->tiq, _texth))->lno : lno);
	return (0);
}