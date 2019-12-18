#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sc; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_6__ {int /*<<< orphan*/ * scr_map; } ;

/* Variables and functions */
 int SC_NORM_ATTR ; 
 int /*<<< orphan*/  mark_all (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_move_cursor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_vtb_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dumb_clear(scr_stat *scp)
{
	sc_move_cursor(scp, 0, 0);
	sc_vtb_clear(&scp->vtb, scp->sc->scr_map[0x20], SC_NORM_ATTR << 8);
	mark_all(scp);
}