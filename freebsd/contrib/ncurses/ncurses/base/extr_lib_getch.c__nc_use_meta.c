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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int _use_meta; } ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 TYPE_1__* _nc_screen_of (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_nc_use_meta(WINDOW *win)
{
    SCREEN *sp = _nc_screen_of(win);
    return (sp ? sp->_use_meta : 0);
}