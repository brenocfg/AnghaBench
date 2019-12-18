#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cur_attr; } ;
typedef  TYPE_2__ term_stat ;
struct TYPE_9__ {TYPE_1__* sc; int /*<<< orphan*/  vtb; TYPE_2__* ts; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_7__ {int /*<<< orphan*/ * scr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_all (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_move_cursor (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_vtb_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scterm_clear(scr_stat *scp)
{
	term_stat *tcp = scp->ts;

	sc_move_cursor(scp, 0, 0);
	sc_vtb_clear(&scp->vtb, scp->sc->scr_map[0x20], tcp->cur_attr);
	mark_all(scp);
}