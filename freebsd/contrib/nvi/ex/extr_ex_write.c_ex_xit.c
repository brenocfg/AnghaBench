#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  iflags; } ;
struct TYPE_12__ {int /*<<< orphan*/  ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 int FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SC_EXIT ; 
 int /*<<< orphan*/  SC_EXIT_FORCE ; 
 int /*<<< orphan*/  XIT ; 
 scalar_t__ ex_ncheck (TYPE_1__*,int) ; 
 scalar_t__ exwr (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_m3 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ex_xit(SCR *sp, EXCMD *cmdp)
{
	int force;

	NEEDFILE(sp, cmdp);

	if (F_ISSET(sp->ep, F_MODIFIED) && exwr(sp, cmdp, XIT))
		return (1);
	if (file_m3(sp, 0))
		return (1);

	force = FL_ISSET(cmdp->iflags, E_C_FORCE);

	if (ex_ncheck(sp, force))
		return (1);

	F_SET(sp, force ? SC_EXIT_FORCE : SC_EXIT);
	return (0);
}