#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ts_teken; } ;
typedef  TYPE_2__ teken_stat ;
struct TYPE_11__ {TYPE_1__* sc; int /*<<< orphan*/  vtb; TYPE_2__* ts; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_9__ {int /*<<< orphan*/ * scr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_all (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_move_cursor (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_vtb_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scteken_sync_internal (TYPE_3__*,TYPE_2__*) ; 
 int scteken_te_to_sc_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken_get_curattr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scteken_clear(scr_stat *scp)
{
	teken_stat *ts = scp->ts;

	sc_move_cursor(scp, 0, 0);
	scteken_sync_internal(scp, ts);
	sc_vtb_clear(&scp->vtb, scp->sc->scr_map[0x20],
		     scteken_te_to_sc_attr(teken_get_curattr(&ts->ts_teken))
		     << 8);
	mark_all(scp);
}