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
struct TYPE_7__ {int /*<<< orphan*/  cursor_pos; int /*<<< orphan*/  cursor_oldpos; TYPE_1__* tsw; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_6__ {int /*<<< orphan*/  (* te_clear ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sc_remove_cutmarking (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
sc_clear_screen(scr_stat *scp)
{
	(*scp->tsw->te_clear)(scp);
	scp->cursor_oldpos = scp->cursor_pos;
	sc_remove_cutmarking(scp);
}