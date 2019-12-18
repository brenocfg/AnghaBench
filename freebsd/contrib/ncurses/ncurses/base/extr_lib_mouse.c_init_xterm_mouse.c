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
struct TYPE_3__ {char* _mouse_xtermcap; int /*<<< orphan*/  _mouse_type; } ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  M_XTERM ; 
 int /*<<< orphan*/  VALID_STRING (char*) ; 
 char* tigetstr (char*) ; 

__attribute__((used)) static void
init_xterm_mouse(SCREEN *sp)
{
    sp->_mouse_type = M_XTERM;
    sp->_mouse_xtermcap = tigetstr("XM");
    if (!VALID_STRING(sp->_mouse_xtermcap))
	sp->_mouse_xtermcap = "\033[?1000%?%p1%{1}%=%th%el%;";
}