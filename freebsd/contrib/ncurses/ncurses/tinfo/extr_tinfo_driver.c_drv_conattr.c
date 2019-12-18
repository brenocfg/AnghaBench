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
typedef  int /*<<< orphan*/  chtype ;
struct TYPE_5__ {scalar_t__ _coloron; } ;
struct TYPE_4__ {TYPE_2__* csp; } ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_2__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  A_ALTCHARSET ; 
 int /*<<< orphan*/  A_BLINK ; 
 int /*<<< orphan*/  A_BOLD ; 
 int /*<<< orphan*/  A_COLOR ; 
 int /*<<< orphan*/  A_DIM ; 
 int /*<<< orphan*/  A_INVIS ; 
 int /*<<< orphan*/  A_ITALIC ; 
 int /*<<< orphan*/  A_NORMAL ; 
 int /*<<< orphan*/  A_PROTECT ; 
 int /*<<< orphan*/  A_REVERSE ; 
 int /*<<< orphan*/  A_STANDOUT ; 
 int /*<<< orphan*/  A_UNDERLINE ; 
 int /*<<< orphan*/  AssertTCB () ; 
 scalar_t__ enter_alt_charset_mode ; 
 scalar_t__ enter_blink_mode ; 
 scalar_t__ enter_bold_mode ; 
 scalar_t__ enter_dim_mode ; 
 scalar_t__ enter_italics_mode ; 
 scalar_t__ enter_protected_mode ; 
 scalar_t__ enter_reverse_mode ; 
 scalar_t__ enter_secure_mode ; 
 scalar_t__ enter_standout_mode ; 
 scalar_t__ enter_underline_mode ; 

__attribute__((used)) static chtype
drv_conattr(TERMINAL_CONTROL_BLOCK * TCB)
{
    SCREEN *sp = TCB->csp;
    chtype attrs = A_NORMAL;

    AssertTCB();
    if (enter_alt_charset_mode)
	attrs |= A_ALTCHARSET;

    if (enter_blink_mode)
	attrs |= A_BLINK;

    if (enter_bold_mode)
	attrs |= A_BOLD;

    if (enter_dim_mode)
	attrs |= A_DIM;

    if (enter_reverse_mode)
	attrs |= A_REVERSE;

    if (enter_standout_mode)
	attrs |= A_STANDOUT;

    if (enter_protected_mode)
	attrs |= A_PROTECT;

    if (enter_secure_mode)
	attrs |= A_INVIS;

    if (enter_underline_mode)
	attrs |= A_UNDERLINE;

    if (sp && sp->_coloron)
	attrs |= A_COLOR;

#if USE_ITALIC
    if (enter_italics_mode)
	attrs |= A_ITALIC;
#endif

    return (attrs);
}