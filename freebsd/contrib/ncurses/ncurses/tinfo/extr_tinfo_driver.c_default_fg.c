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
struct TYPE_3__ {int _default_fg; } ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int COLOR_WHITE ; 

__attribute__((used)) static int
default_fg(SCREEN *sp)
{
#if NCURSES_EXT_FUNCS
    return (sp != 0) ? sp->_default_fg : COLOR_WHITE;
#else
    return COLOR_WHITE;
#endif
}