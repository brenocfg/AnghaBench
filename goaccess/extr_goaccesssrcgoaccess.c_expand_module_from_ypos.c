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
struct TYPE_4__ {int expanded; int /*<<< orphan*/  current; } ;

/* Variables and functions */
 int LINES ; 
 int MAX_HEIGHT_HEADER ; 
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  allocate_holder_by_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_holder_by_module (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ gscroll ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  render_screens () ; 
 int /*<<< orphan*/  reset_scroll_offsets (TYPE_1__*) ; 
 scalar_t__ set_module_from_mouse_event (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
expand_module_from_ypos (int y)
{
  /* ignore header/footer clicks */
  if (y < MAX_HEIGHT_HEADER || y == LINES - 1)
    return;

  if (set_module_from_mouse_event (&gscroll, dash, y))
    return;

  reset_scroll_offsets (&gscroll);
  gscroll.expanded = 1;

  free_holder_by_module (&holder, gscroll.current);
  free_dashboard (dash);
  allocate_holder_by_module (gscroll.current);
  allocate_data ();

  render_screens ();
}