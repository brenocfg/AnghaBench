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
struct TYPE_3__ {int current; scalar_t__ dash; scalar_t__ expanded; } ;
typedef  TYPE_1__ GScroll ;
typedef  int /*<<< orphan*/  GDash ;

/* Variables and functions */
 int DASH_COLLAPSED ; 
 int MAX_HEIGHT_FOOTER ; 
 int MAX_HEIGHT_HEADER ; 
 int TOTAL_MODULES ; 
 int get_find_current_module (int /*<<< orphan*/ *,int) ; 

int
set_module_from_mouse_event (GScroll * gscroll, GDash * dash, int y)
{
  int module = 0;
  int offset = y - MAX_HEIGHT_HEADER - MAX_HEIGHT_FOOTER + 1;
  if (gscroll->expanded) {
    module = get_find_current_module (dash, offset);
  } else {
    offset += gscroll->dash;
    module = offset / DASH_COLLAPSED;
  }

  if (module >= TOTAL_MODULES)
    module = TOTAL_MODULES - 1;
  else if (module < 0)
    module = 0;

  if ((int) gscroll->current == module)
    return 1;

  gscroll->current = module;
  return 0;
}