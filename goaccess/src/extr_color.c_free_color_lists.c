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
 int /*<<< orphan*/ * color_list ; 
 int /*<<< orphan*/  list_remove_nodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pair_list ; 

void
free_color_lists (void)
{
  if (pair_list)
    list_remove_nodes (pair_list);
  if (color_list)
    list_remove_nodes (color_list);
  color_list = NULL;
  pair_list = NULL;
}