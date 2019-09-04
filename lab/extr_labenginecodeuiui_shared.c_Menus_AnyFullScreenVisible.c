#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {scalar_t__ fullScreen; TYPE_1__ window; } ;

/* Variables and functions */
 TYPE_2__* Menus ; 
 int WINDOW_VISIBLE ; 
 int menuCount ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Menus_AnyFullScreenVisible(void) {
  int i;
  for (i = 0; i < menuCount; i++) {
    if (Menus[i].window.flags & WINDOW_VISIBLE && Menus[i].fullScreen) {
			return qtrue;
    }
  }
  return qfalse;
}