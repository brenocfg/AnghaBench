#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  tui_set_locator_filename (char const*) ; 
 int /*<<< orphan*/  tui_show_locator_content () ; 

void
tui_update_locator_filename (const char *filename)
{
  tui_set_locator_filename (filename);
  tui_show_locator_content ();
}