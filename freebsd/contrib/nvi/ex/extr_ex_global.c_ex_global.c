#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iflags; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL ; 
 int /*<<< orphan*/  V ; 
 int ex_g_setup (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ex_global(SCR *sp, EXCMD *cmdp)
{
	return (ex_g_setup(sp,
	    cmdp, FL_ISSET(cmdp->iflags, E_C_FORCE) ? V : GLOBAL));
}