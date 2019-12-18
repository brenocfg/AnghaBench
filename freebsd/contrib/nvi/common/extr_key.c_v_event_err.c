#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int e_event; int /*<<< orphan*/ * e_asp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EVENT ;

/* Variables and functions */
#define  E_CHARACTER 137 
#define  E_EOF 136 
#define  E_ERR 135 
#define  E_INTERRUPT 134 
#define  E_REPAINT 133 
#define  E_SIGHUP 132 
#define  E_SIGTERM 131 
#define  E_STRING 130 
#define  E_TIMEOUT 129 
#define  E_WRESIZE 128 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
v_event_err(
	SCR *sp,
	EVENT *evp)
{
	switch (evp->e_event) {
	case E_CHARACTER:
		msgq(sp, M_ERR, "276|Unexpected character event");
		break;
	case E_EOF:
		msgq(sp, M_ERR, "277|Unexpected end-of-file event");
		break;
	case E_INTERRUPT:
		msgq(sp, M_ERR, "279|Unexpected interrupt event");
		break;
	case E_REPAINT:
		msgq(sp, M_ERR, "281|Unexpected repaint event");
		break;
	case E_STRING:
		msgq(sp, M_ERR, "285|Unexpected string event");
		break;
	case E_TIMEOUT:
		msgq(sp, M_ERR, "286|Unexpected timeout event");
		break;
	case E_WRESIZE:
		msgq(sp, M_ERR, "316|Unexpected resize event");
		break;

	/*
	 * Theoretically, none of these can occur, as they're handled at the
	 * top editor level.
	 */
	case E_ERR:
	case E_SIGHUP:
	case E_SIGTERM:
	default:
		abort();
	}

	/* Free any allocated memory. */
	if (evp->e_asp != NULL)
		free(evp->e_asp);
}