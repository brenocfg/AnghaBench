#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  no_tab_scroll; } ;
struct TYPE_6__ {int dash; } ;
struct TYPE_5__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ GScroll ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int DASH_COLLAPSED ; 
 int /*<<< orphan*/  collapse_current_module () ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  disabled_panel_msg (int /*<<< orphan*/ ) ; 
 int get_module_index (int /*<<< orphan*/ ) ; 
 TYPE_3__ gscroll ; 
 int /*<<< orphan*/  render_screens () ; 

__attribute__((used)) static void
set_module_to (GScroll * scrll, GModule module)
{
  if (get_module_index (module) == -1) {
    disabled_panel_msg (module);
    return;
  }

  /* scroll to panel */
  if (!conf.no_tab_scroll)
    gscroll.dash = get_module_index (module) * DASH_COLLAPSED;

  /* reset expanded module */
  collapse_current_module ();
  scrll->current = module;
  render_screens ();
}