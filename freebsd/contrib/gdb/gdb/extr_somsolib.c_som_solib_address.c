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
struct TYPE_2__ {scalar_t__ text_addr; scalar_t__ text_end; char* name; } ;
struct so_list {struct so_list* next; TYPE_1__ som_solib; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct so_list* so_list_head ; 

char *
som_solib_address (CORE_ADDR addr)
{
  struct so_list *so = so_list_head;

  while (so)
    {
      /* Is this address within this shlib's text range?  If so,
         return the shlib's name.
       */
      if ((addr >= so->som_solib.text_addr) && (addr <= so->som_solib.text_end))
	return so->som_solib.name;

      /* Nope, keep looking... */
      so = so->next;
    }

  /* No, we couldn't prove that the address is within a shlib. */
  return NULL;
}