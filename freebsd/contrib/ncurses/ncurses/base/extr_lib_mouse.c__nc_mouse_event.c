#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; int buttons; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  bstate; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int _mouse_type; int _mouse_fd; size_t _sysmouse_head; size_t _sysmouse_tail; size_t _drv_mouse_head; size_t _drv_mouse_tail; TYPE_2__* _mouse_eventp; TYPE_2__* _drv_mouse_fifo; TYPE_2__* _sysmouse_fifo; } ;
typedef  TYPE_1__ SCREEN ;
typedef  TYPE_2__ MEVENT ;
typedef  TYPE_3__ Gpm_Event ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON1_PRESSED ; 
 int /*<<< orphan*/  BUTTON1_RELEASED ; 
 int /*<<< orphan*/  BUTTON2_PRESSED ; 
 int /*<<< orphan*/  BUTTON2_RELEASED ; 
 int /*<<< orphan*/  BUTTON3_PRESSED ; 
 int /*<<< orphan*/  BUTTON3_RELEASED ; 
 int FALSE ; 
 int GPM_B_LEFT ; 
 int GPM_B_MIDDLE ; 
 int GPM_B_RIGHT ; 
 int GPM_DOWN ; 
 int GPM_UP ; 
 int /*<<< orphan*/  M_FD (TYPE_1__*) ; 
#define  M_GPM 132 
#define  M_NONE 131 
#define  M_SYSMOUSE 130 
#define  M_TERM_DRIVER 129 
#define  M_XTERM 128 
 void* NEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  NORMAL_EVENT ; 
 int /*<<< orphan*/  REPORT_MOUSE_POSITION ; 
 int TRUE ; 
 char* key_mouse ; 
 int /*<<< orphan*/  my_Gpm_GetEvent (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int read (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static bool
_nc_mouse_event(SCREEN *sp)
{
    MEVENT *eventp = sp->_mouse_eventp;
    bool result = FALSE;

    (void) eventp;

    switch (sp->_mouse_type) {
    case M_XTERM:
	/* xterm: never have to query, mouse events are in the keyboard stream */
#if USE_EMX_MOUSE
	{
	    char kbuf[3];

	    int i, res = read(M_FD(sp), &kbuf, 3);	/* Eat the prefix */
	    if (res != 3)
		printf("Got %d chars instead of 3 for prefix.\n", res);
	    for (i = 0; i < res; i++) {
		if (kbuf[i] != key_mouse[i])
		    printf("Got char %d instead of %d for prefix.\n",
			   (int) kbuf[i], (int) key_mouse[i]);
	    }
	    result = TRUE;
	}
#endif /* USE_EMX_MOUSE */
	break;

#if USE_GPM_SUPPORT
    case M_GPM:
	if (sp->_mouse_fd >= 0) {
	    /* query server for event, return TRUE if we find one */
	    Gpm_Event ev;

	    switch (my_Gpm_GetEvent(&ev)) {
	    case 0:
		/* Connection closed, drop the mouse. */
		sp->_mouse_fd = -1;
		break;
	    case 1:
		/* there's only one mouse... */
		eventp->id = NORMAL_EVENT;

		eventp->bstate = 0;
		switch (ev.type & 0x0f) {
		case (GPM_DOWN):
		    if (ev.buttons & GPM_B_LEFT)
			eventp->bstate |= BUTTON1_PRESSED;
		    if (ev.buttons & GPM_B_MIDDLE)
			eventp->bstate |= BUTTON2_PRESSED;
		    if (ev.buttons & GPM_B_RIGHT)
			eventp->bstate |= BUTTON3_PRESSED;
		    break;
		case (GPM_UP):
		    if (ev.buttons & GPM_B_LEFT)
			eventp->bstate |= BUTTON1_RELEASED;
		    if (ev.buttons & GPM_B_MIDDLE)
			eventp->bstate |= BUTTON2_RELEASED;
		    if (ev.buttons & GPM_B_RIGHT)
			eventp->bstate |= BUTTON3_RELEASED;
		    break;
		default:
		    eventp->bstate |= REPORT_MOUSE_POSITION;
		    break;
		}

		eventp->x = ev.x - 1;
		eventp->y = ev.y - 1;
		eventp->z = 0;

		/* bump the next-free pointer into the circular list */
		sp->_mouse_eventp = NEXT(eventp);
		result = TRUE;
		break;
	    }
	}
	break;
#endif

#if USE_SYSMOUSE
    case M_SYSMOUSE:
	if (sp->_sysmouse_head < sp->_sysmouse_tail) {
	    *eventp = sp->_sysmouse_fifo[sp->_sysmouse_head];

	    /*
	     * Point the fifo-head to the next possible location.  If there
	     * are none, reset the indices.  This may be interrupted by the
	     * signal handler, doing essentially the same reset.
	     */
	    sp->_sysmouse_head += 1;
	    if (sp->_sysmouse_head == sp->_sysmouse_tail) {
		sp->_sysmouse_tail = 0;
		sp->_sysmouse_head = 0;
	    }

	    /* bump the next-free pointer into the circular list */
	    sp->_mouse_eventp = eventp = NEXT(eventp);
	    result = TRUE;
	}
	break;
#endif /* USE_SYSMOUSE */

#ifdef USE_TERM_DRIVER
    case M_TERM_DRIVER:
	while (sp->_drv_mouse_head < sp->_drv_mouse_tail) {
	    *eventp = sp->_drv_mouse_fifo[sp->_drv_mouse_head];

	    /*
	     * Point the fifo-head to the next possible location.  If there
	     * are none, reset the indices.
	     */
	    sp->_drv_mouse_head += 1;
	    if (sp->_drv_mouse_head == sp->_drv_mouse_tail) {
		sp->_drv_mouse_tail = 0;
		sp->_drv_mouse_head = 0;
	    }

	    /* bump the next-free pointer into the circular list */
	    sp->_mouse_eventp = eventp = NEXT(eventp);
	    result = TRUE;
	}
	break;
#endif

    case M_NONE:
	break;
    }

    return result;		/* true if we found an event */
}