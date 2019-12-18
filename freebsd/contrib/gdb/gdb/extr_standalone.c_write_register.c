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
typedef  int /*<<< orphan*/  REGISTER_TYPE ;

/* Variables and functions */
 int NUM_REGS ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/ * saved_regs ; 

void
write_register (int regno, REGISTER_TYPE value)
{
  if (regno < 0 || regno >= NUM_REGS)
    error ("Register number %d out of range.", regno);
  saved_regs[regno] = value;
}