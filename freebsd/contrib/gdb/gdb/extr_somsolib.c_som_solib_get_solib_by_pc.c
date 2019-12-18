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
struct TYPE_2__ {scalar_t__ text_addr; scalar_t__ text_end; } ;
struct so_list {scalar_t__ solib_addr; struct so_list* next; TYPE_1__ som_solib; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct so_list* so_list_head ; 

CORE_ADDR
som_solib_get_solib_by_pc (CORE_ADDR addr)
{
  struct so_list *so_list = so_list_head;

  while (so_list)
    {
      if (so_list->som_solib.text_addr <= addr
	  && so_list->som_solib.text_end > addr)
	{
	  break;
	}
      so_list = so_list->next;
    }
  if (so_list)
    return so_list->solib_addr;
  else
    return 0;
}