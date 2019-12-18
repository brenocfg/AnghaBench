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
struct TYPE_5__ {TYPE_1__** argv; int /*<<< orphan*/  iflags; } ;
struct TYPE_4__ {int /*<<< orphan*/  bp; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  SEQ_COMMAND ; 
 int /*<<< orphan*/  SEQ_INPUT ; 
 int /*<<< orphan*/  msgq_wstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ seq_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_unmap(SCR *sp, EXCMD *cmdp)
{
	if (seq_delete(sp, cmdp->argv[0]->bp, cmdp->argv[0]->len,
	    FL_ISSET(cmdp->iflags, E_C_FORCE) ? SEQ_INPUT : SEQ_COMMAND)) {
		msgq_wstr(sp, M_INFO,
		    cmdp->argv[0]->bp, "135|\"%s\" isn't currently mapped");
		return (1);
	}
	return (0);
}