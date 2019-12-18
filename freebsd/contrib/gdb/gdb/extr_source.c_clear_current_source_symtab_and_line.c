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
 scalar_t__ current_source_line ; 
 scalar_t__ current_source_symtab ; 

void
clear_current_source_symtab_and_line (void)
{
  current_source_symtab = 0;
  current_source_line = 0;
}