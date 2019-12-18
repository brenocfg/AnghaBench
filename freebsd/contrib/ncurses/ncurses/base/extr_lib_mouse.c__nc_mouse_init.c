#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int _mouse_initialized; int /*<<< orphan*/  _mouse_type; scalar_t__ _mouse_events; int /*<<< orphan*/  _mouse_eventp; } ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int EV_MAX ; 
 int FALSE ; 
 int /*<<< orphan*/  FirstEV (TYPE_1__*) ; 
 int /*<<< orphan*/  Invalidate (scalar_t__) ; 
 int /*<<< orphan*/  MY_TRACE ; 
 int /*<<< orphan*/  T (char*) ; 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  initialize_mousetype (TYPE_1__*) ; 

__attribute__((used)) static bool
_nc_mouse_init(SCREEN *sp)
/* initialize the mouse */
{
    bool result = FALSE;
    int i;

    if (sp != 0) {
	if (!sp->_mouse_initialized) {
	    sp->_mouse_initialized = TRUE;

	    TR(MY_TRACE, ("_nc_mouse_init() called"));

	    sp->_mouse_eventp = FirstEV(sp);
	    for (i = 0; i < EV_MAX; i++)
		Invalidate(sp->_mouse_events + i);

	    initialize_mousetype(sp);

	    T(("_nc_mouse_init() set mousetype to %d", sp->_mouse_type));
	}
	result = sp->_mouse_initialized;
    }
    return result;
}