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
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int TOTAL_MODULES ; 
 int get_module_index (int /*<<< orphan*/ ) ; 
 int* module_list ; 

int
get_next_module (GModule module)
{
  int next = get_module_index (module) + 1;

  if (next == TOTAL_MODULES || module_list[next] == -1)
    return module_list[0];

  return module_list[next];
}