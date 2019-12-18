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
 int FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EXIT ; 
 int /*<<< orphan*/  SC_EXIT_FORCE ; 
 int /*<<< orphan*/  WQ ; 
 scalar_t__ ex_ncheck (int /*<<< orphan*/ *,int) ; 
 scalar_t__ exwr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_m3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ex_wq(SCR *sp, EXCMD *cmdp)
{
	int force;

	if (exwr(sp, cmdp, WQ))
		return (1);
	if (file_m3(sp, 0))
		return (1);

	force = FL_ISSET(cmdp->iflags, E_C_FORCE);

	if (ex_ncheck(sp, force))
		return (1);

	F_SET(sp, force ? SC_EXIT_FORCE : SC_EXIT);
	return (0);
}