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
 int get_tlist_size (int /*<<< orphan*/ *) ; 

void get_running_lists_size (int *child_size, int *auto_size) {
  *child_size = get_tlist_size (&child_running_list);
  *auto_size = get_tlist_size (&auto_running_list);
}