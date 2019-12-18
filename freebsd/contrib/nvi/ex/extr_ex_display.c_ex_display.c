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
struct TYPE_8__ {int* bp; } ;
struct TYPE_7__ {TYPE_1__* cmd; TYPE_3__** argv; } ;
struct TYPE_6__ {int /*<<< orphan*/  usage; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;
typedef  TYPE_3__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_USAGE ; 
 int /*<<< orphan*/  L (char*) ; 
 int bdisplay (int /*<<< orphan*/ *) ; 
 int cscope_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_emsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ex_sdisplay (int /*<<< orphan*/ *) ; 
 int ex_tag_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_prefix (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
ex_display(SCR *sp, EXCMD *cmdp)
{
	ARGS *arg;

	arg = cmdp->argv[0];

	switch (arg->bp[0]) {
	case 'b':
		if (!is_prefix(arg, L("buffers")))
			break;
		return (bdisplay(sp));
	case 'c':
		if (!is_prefix(arg, L("connections")))
			break;
		return (cscope_display(sp));
	case 's':
		if (!is_prefix(arg, L("screens")))
			break;
		return (ex_sdisplay(sp));
	case 't':
		if (!is_prefix(arg, L("tags")))
			break;
		return (ex_tag_display(sp));
	}
	ex_emsg(sp, cmdp->cmd->usage, EXM_USAGE);
	return (1);
}