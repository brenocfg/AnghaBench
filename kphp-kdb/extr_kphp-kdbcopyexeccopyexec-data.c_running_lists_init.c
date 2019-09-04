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
 int /*<<< orphan*/  auto_running_list ; 
 int /*<<< orphan*/  child_running_list ; 
 int /*<<< orphan*/  tlist_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

void running_lists_init (void) {
  tlist_clear (&child_running_list);
  vkprintf (4, "tlist_clear (&auto_running_list)\n");
  tlist_clear (&auto_running_list);
}