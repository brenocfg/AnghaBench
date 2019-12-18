#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ts_busy; int /*<<< orphan*/  ts_teken; } ;
typedef  TYPE_1__ teken_stat ;
typedef  int /*<<< orphan*/  teken_attr_t ;
typedef  int /*<<< orphan*/  scr_stat ;
struct TYPE_7__ {scalar_t__ ts_busy; } ;
struct TYPE_6__ {int /*<<< orphan*/  te_refcount; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SC_TE_COLD_INIT 129 
#define  SC_TE_WARM_INIT 128 
 TYPE_4__ reserved_teken_stat ; 
 TYPE_3__ sc_term_scteken ; 
 int /*<<< orphan*/  scteken_funcs ; 
 int /*<<< orphan*/  scteken_sync_internal (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * teken_get_defattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_8bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_cons25 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_cons25keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_defattr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
scteken_init(scr_stat *scp, void **softc, int code)
{
	teken_stat *ts;
	teken_attr_t ta;

	if (*softc == NULL) {
		if (reserved_teken_stat.ts_busy)
			return (EINVAL);
		*softc = &reserved_teken_stat;
	}
	ts = *softc;

	switch (code) {
	case SC_TE_COLD_INIT:
		++sc_term_scteken.te_refcount;
		ts->ts_busy = 1;
		/* FALLTHROUGH */
	case SC_TE_WARM_INIT:
		ta = *teken_get_defattr(&ts->ts_teken);
		teken_init(&ts->ts_teken, &scteken_funcs, scp);
		teken_set_defattr(&ts->ts_teken, &ta);
#ifndef TEKEN_UTF8
		teken_set_8bit(&ts->ts_teken);
#endif /* !TEKEN_UTF8 */
#ifdef TEKEN_CONS25
		teken_set_cons25(&ts->ts_teken);
#endif /* TEKEN_CONS25 */
		teken_set_cons25keys(&ts->ts_teken);
		scteken_sync_internal(scp, ts);
		break;
	}

	return (0);
}