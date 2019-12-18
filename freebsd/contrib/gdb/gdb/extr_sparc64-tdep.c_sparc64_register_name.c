#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 int SPARC64_NUM_PSEUDO_REGS ; 
 int SPARC64_NUM_REGS ; 
 TYPE_2__* sparc64_pseudo_register_info ; 
 TYPE_1__* sparc64_register_info ; 

__attribute__((used)) static const char *
sparc64_register_name (int regnum)
{
  if (regnum >= 0 && regnum < SPARC64_NUM_REGS)
    return sparc64_register_info[regnum].name;

  if (regnum >= SPARC64_NUM_REGS
      && regnum < SPARC64_NUM_REGS + SPARC64_NUM_PSEUDO_REGS)
    return sparc64_pseudo_register_info[regnum - SPARC64_NUM_REGS].name;

  return NULL;
}