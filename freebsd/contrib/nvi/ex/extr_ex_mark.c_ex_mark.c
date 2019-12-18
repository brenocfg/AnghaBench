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
struct TYPE_6__ {int /*<<< orphan*/  addr1; TYPE_1__** argv; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * bp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  NEEDFILE (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mark_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
ex_mark(SCR *sp, EXCMD *cmdp)
{
	NEEDFILE(sp, cmdp);

	if (cmdp->argv[0]->len != 1) {
		msgq(sp, M_ERR, "136|Mark names must be a single character");
		return (1);
	}
	return (mark_set(sp, cmdp->argv[0]->bp[0], &cmdp->addr1, 1));
}