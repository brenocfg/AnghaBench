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
struct symtab_and_line {scalar_t__ end; scalar_t__ pc; scalar_t__ line; scalar_t__ section; scalar_t__ symtab; } ;

/* Variables and functions */

void
init_sal (struct symtab_and_line *sal)
{
  sal->symtab = 0;
  sal->section = 0;
  sal->line = 0;
  sal->pc = 0;
  sal->end = 0;
}