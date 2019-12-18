#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_6__ {TYPE_1__* cmd; } ;
struct TYPE_5__ {int (* fn ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ v_ex_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
v_exec_ex(SCR *sp, VICMD *vp, EXCMD *exp)
{
	int rval;

	rval = exp->cmd->fn(sp, exp);
	return (v_ex_done(sp, vp) || rval);
}