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
struct TYPE_4__ {scalar_t__ argc; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  SC_VI ; 
 scalar_t__ ex_edit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sscr_init (int /*<<< orphan*/ *) ; 

int
ex_script(SCR *sp, EXCMD *cmdp)
{
	/* Vi only command. */
	if (!F_ISSET(sp, SC_VI)) {
		msgq(sp, M_ERR,
		    "150|The script command is only available in vi mode");
		return (1);
	}

	/* Switch to the new file. */
	if (cmdp->argc != 0 && ex_edit(sp, cmdp))
		return (1);

	/* Create the shell, figure out the prompt. */
	if (sscr_init(sp))
		return (1);

	return (0);
}