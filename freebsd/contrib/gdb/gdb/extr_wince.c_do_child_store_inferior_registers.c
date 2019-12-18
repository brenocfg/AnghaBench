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
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int NUM_REGS ; 
 TYPE_1__* current_thread ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,char*) ; 
 int* mappings ; 

__attribute__((used)) static void
do_child_store_inferior_registers (int r)
{
  if (r >= 0)
    deprecated_read_register_gen (r, ((char *) &current_thread->context) + mappings[r]);
  else
    {
      for (r = 0; r < NUM_REGS; r++)
	do_child_store_inferior_registers (r);
    }
}