#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ignore_panel_idx; int /*<<< orphan*/ * ignore_panels; } ;
typedef  unsigned int GModule ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int get_module_enum (int /*<<< orphan*/ ) ; 

int
ignore_panel (GModule mod)
{
  int i, module;

  for (i = 0; i < conf.ignore_panel_idx; ++i) {
    if ((module = get_module_enum (conf.ignore_panels[i])) == -1)
      continue;
    if (mod == (unsigned int) module) {
      return 1;
    }
  }

  return 0;
}