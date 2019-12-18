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
 int SPARC32_NUM_PSEUDO_REGS ; 
 int SPARC32_NUM_REGS ; 
 char const** sparc32_pseudo_register_names ; 
 char const** sparc32_register_names ; 

__attribute__((used)) static const char *
sparc32_register_name (int regnum)
{
  if (regnum >= 0 && regnum < SPARC32_NUM_REGS)
    return sparc32_register_names[regnum];

  if (regnum < SPARC32_NUM_REGS + SPARC32_NUM_PSEUDO_REGS)
    return sparc32_pseudo_register_names[regnum - SPARC32_NUM_REGS];

  return NULL;
}