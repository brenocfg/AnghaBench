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
struct TYPE_3__ {scalar_t__ expanded; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 TYPE_1__ gscroll ; 
 int /*<<< orphan*/  render_screens () ; 
 int /*<<< orphan*/  reset_scroll_offsets (TYPE_1__*) ; 

__attribute__((used)) static void
collapse_current_module (void)
{
  if (!gscroll.expanded)
    return;

  gscroll.expanded = 0;
  reset_scroll_offsets (&gscroll);
  free_dashboard (dash);
  allocate_data ();
  render_screens ();
}