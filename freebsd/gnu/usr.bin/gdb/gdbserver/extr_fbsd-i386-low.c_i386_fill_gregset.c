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
 int /*<<< orphan*/  collect_register (int,char*) ; 
 int i386_num_regs ; 
 int* i386_regmap ; 

__attribute__((used)) static void
i386_fill_gregset (void *buf)
{
  int i;

  for (i = 0; i < i386_num_regs; i++)
    collect_register (i, ((char *) buf) + i386_regmap[i]);

}