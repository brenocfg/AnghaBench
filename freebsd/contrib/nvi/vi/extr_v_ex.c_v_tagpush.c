#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_2__ {int /*<<< orphan*/  keyw; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  C_TAG ; 
 int /*<<< orphan*/  OOBLNO ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ ) ; 
 TYPE_1__* VIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v_exec_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_tagpush(SCR *sp, VICMD *vp)
{
	EXCMD cmd;

	ex_cinit(sp, &cmd, C_TAG, 0, OOBLNO, 0, 0);
	argv_exp0(sp, &cmd, VIP(sp)->keyw, STRLEN(VIP(sp)->keyw) + 1);
	return (v_exec_ex(sp, vp, &cmd));
}