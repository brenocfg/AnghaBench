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
struct so_stuff {scalar_t__ load_addr; scalar_t__ end_addr; char* name; struct so_stuff* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct so_stuff solib_start ; 

char *
solib_address (CORE_ADDR address)
{
  struct so_stuff *so;
  for (so = &solib_start; so->next != NULL; so = so->next)
    if (address >= so->load_addr && address <= so->end_addr)
      return so->name;
  return NULL;
}