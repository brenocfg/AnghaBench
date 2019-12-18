#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lno; } ;
struct TYPE_6__ {int /*<<< orphan*/  lno; } ;
struct TYPE_8__ {TYPE_2__ m_stop; TYPE_1__ m_start; } ;
typedef  TYPE_3__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  C_SHIFTL ; 
 int /*<<< orphan*/  L (char*) ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v_exec_ex (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

int
v_shiftl(SCR *sp, VICMD *vp)
{
	EXCMD cmd;

	ex_cinit(sp, &cmd, C_SHIFTL, 2, vp->m_start.lno, vp->m_stop.lno, 0);
	argv_exp0(sp, &cmd, L("<"), 2);
	return (v_exec_ex(sp, vp, &cmd));
}