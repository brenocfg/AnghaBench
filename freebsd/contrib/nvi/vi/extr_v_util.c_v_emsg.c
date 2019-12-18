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
typedef  int vim_t ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_BERR ; 
 int /*<<< orphan*/  M_ERR ; 
#define  VIM_COMBUF 135 
#define  VIM_EMPTY 134 
#define  VIM_EOF 133 
#define  VIM_EOL 132 
#define  VIM_NOCOM 131 
#define  VIM_NOCOM_B 130 
#define  VIM_USAGE 129 
#define  VIM_WRESIZE 128 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

void
v_emsg(SCR *sp, char *p, vim_t which)
{
	switch (which) {
	case VIM_COMBUF:
		msgq(sp, M_ERR,
		    "201|Buffers should be specified before the command");
		break;
	case VIM_EMPTY:
		msgq(sp, M_BERR, "209|The file is empty");
		break;
	case VIM_EOF:
		msgq(sp, M_BERR, "202|Already at end-of-file");
		break;
	case VIM_EOL:
		msgq(sp, M_BERR, "203|Already at end-of-line");
		break;
	case VIM_NOCOM:
	case VIM_NOCOM_B:
		msgq(sp,
		    which == VIM_NOCOM_B ? M_BERR : M_ERR,
		    "204|%s isn't a vi command", p);
		break;
	case VIM_WRESIZE:
		msgq(sp, M_ERR, "Window resize interrupted text input mode");
		break;
	case VIM_USAGE:
		msgq(sp, M_ERR, "205|Usage: %s", p);
		break;
	}
}