#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  C_STOP ; 
 int /*<<< orphan*/  L (char*) ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v_exec_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_suspend(SCR *sp, VICMD *vp)
{
	EXCMD cmd;

	ex_cinit(sp, &cmd, C_STOP, 0, OOBLNO, OOBLNO, 0);
	argv_exp0(sp, &cmd, L("suspend"), SIZE(L("suspend")));
	return (v_exec_ex(sp, vp, &cmd));
}