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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int num_registers ; 
 TYPE_1__* reg_defs ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int
find_regno (const char *name)
{
  int i;

  for (i = 0; i < num_registers; i++)
    if (!strcmp (name, reg_defs[i].name))
      return i;
  fatal ("Unknown register %s requested", name);
  return -1;
}