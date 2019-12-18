#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* gp; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* scr_refresh ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* scr_move ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  LASTLINE (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
vs_home(SCR *sp)
{
	(void)sp->gp->scr_move(sp, LASTLINE(sp), 0);
	(void)sp->gp->scr_refresh(sp, 0);
}