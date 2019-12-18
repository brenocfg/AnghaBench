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
struct TYPE_4__ {int _mouse_type; int /*<<< orphan*/  _mouse_mask; } ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  MY_TRACE ; 
#define  M_GPM 132 
#define  M_NONE 131 
#define  M_SYSMOUSE 130 
#define  M_TERM_DRIVER 129 
#define  M_XTERM 128 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mouse_activate (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_nc_mouse_resume(SCREEN *sp)
/* re-connect to mouse -- called by doupdate() after shellout */
{
    TR(MY_TRACE, ("_nc_mouse_resume() called"));

    switch (sp->_mouse_type) {
    case M_XTERM:
	/* xterm: re-enable reporting */
	if (sp->_mouse_mask)
	    mouse_activate(sp, TRUE);
	break;

#if USE_GPM_SUPPORT
    case M_GPM:
	/* GPM: reclaim our event set */
	if (sp->_mouse_mask)
	    mouse_activate(sp, TRUE);
	break;
#endif

#if USE_SYSMOUSE
    case M_SYSMOUSE:
	mouse_activate(sp, TRUE);
	break;
#endif

#ifdef USE_TERM_DRIVER
    case M_TERM_DRIVER:
	mouse_activate(sp, TRUE);
	break;
#endif

    case M_NONE:
	break;
    }
}