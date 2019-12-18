#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* scr_attr ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* scr_screen ) (TYPE_1__*,int) ;} ;
struct TYPE_9__ {void* cols; void* rows; TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  O_COLUMNS ; 
 int /*<<< orphan*/  O_LINES ; 
 void* O_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ALTERNATE ; 
 int SC_EX ; 
 int SC_SCR_EX ; 
 int /*<<< orphan*/  SC_VI ; 
 scalar_t__ stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_init(SCR *sp)
{
	GS *gp;

	gp = sp->gp;

	if (gp->scr_screen(sp, SC_EX))
		return (1);
	(void)gp->scr_attr(sp, SA_ALTERNATE, 0);

	sp->rows = O_VAL(sp, O_LINES);
	sp->cols = O_VAL(sp, O_COLUMNS);

	F_CLR(sp, SC_VI);
	F_SET(sp, SC_EX | SC_SCR_EX);
	return (0);
}