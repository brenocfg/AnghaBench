#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iflags; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 int FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EXIT ; 
 int /*<<< orphan*/  SC_EXIT_FORCE ; 
 scalar_t__ ex_ncheck (int /*<<< orphan*/ *,int) ; 
 scalar_t__ file_m2 (int /*<<< orphan*/ *,int) ; 

int
ex_quit(SCR *sp, EXCMD *cmdp)
{
	int force;

	force = FL_ISSET(cmdp->iflags, E_C_FORCE);

	/* Check for file modifications, or more files to edit. */
	if (file_m2(sp, force) || ex_ncheck(sp, force))
		return (1);

	F_SET(sp, force ? SC_EXIT_FORCE : SC_EXIT);
	return (0);
}