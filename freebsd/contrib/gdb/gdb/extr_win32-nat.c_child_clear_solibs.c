#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct so_stuff {struct so_stuff* next; } ;
struct TYPE_3__ {int /*<<< orphan*/ * objfile; struct so_stuff* next; } ;

/* Variables and functions */
 int max_dll_name_len ; 
 TYPE_1__* solib_end ; 
 TYPE_1__ solib_start ; 
 int /*<<< orphan*/  xfree (struct so_stuff*) ; 

void
child_clear_solibs (void)
{
  struct so_stuff *so, *so1 = solib_start.next;

  while ((so = so1) != NULL)
    {
      so1 = so->next;
      xfree (so);
    }

  solib_start.next = NULL;
  solib_start.objfile = NULL;
  solib_end = &solib_start;
  max_dll_name_len = sizeof ("DLL Name") - 1;
}