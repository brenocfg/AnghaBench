#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int argc; TYPE_1__* cmd; int /*<<< orphan*/  argv; } ;
struct TYPE_4__ {int /*<<< orphan*/  usage; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGED_DISPLAY ; 
 int /*<<< orphan*/  opts_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opts_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_set(SCR *sp, EXCMD *cmdp)
{
	switch(cmdp->argc) {
	case 0:
		opts_dump(sp, CHANGED_DISPLAY);
		break;
	default:
		if (opts_set(sp, cmdp->argv, cmdp->cmd->usage))
			return (1);
		break;
	}
	return (0);
}