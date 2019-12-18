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
typedef  int u_long ;
struct TYPE_7__ {TYPE_1__* gp; } ;
struct TYPE_6__ {scalar_t__ (* scr_baud ) (TYPE_2__*,int*) ;} ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 int f_window (TYPE_2__*,int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ stub1 (TYPE_2__*,int*) ; 

int
f_w1200(
	SCR *sp,
	OPTION *op,
	char *str,
	u_long *valp)
{
	u_long v;

	/* Historical behavior for w1200 was == 1200. */
	if (sp->gp->scr_baud(sp, &v))
		return (1);
	if (v < 1200 || v > 4800)
		return (0);

	return (f_window(sp, op, str, valp));
}