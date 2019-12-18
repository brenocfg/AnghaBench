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
struct TYPE_3__ {int expanded; scalar_t__ current; } ;

/* Variables and functions */
 scalar_t__ HOSTS ; 
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  allocate_holder_by_module (scalar_t__) ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_holder_by_module (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ gscroll ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  load_ip_agent_list () ; 
 int /*<<< orphan*/  reset_scroll_offsets (TYPE_1__*) ; 

__attribute__((used)) static void
expand_current_module (void)
{
  if (gscroll.expanded && gscroll.current == HOSTS) {
    load_ip_agent_list ();
    return;
  }

  /* expanded, nothing to do... */
  if (gscroll.expanded)
    return;

  reset_scroll_offsets (&gscroll);
  gscroll.expanded = 1;

  free_holder_by_module (&holder, gscroll.current);
  free_dashboard (dash);
  allocate_holder_by_module (gscroll.current);
  allocate_data ();
}