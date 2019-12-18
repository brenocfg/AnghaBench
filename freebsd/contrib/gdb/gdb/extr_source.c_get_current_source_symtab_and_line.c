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
struct symtab_and_line {scalar_t__ end; scalar_t__ pc; int /*<<< orphan*/  line; int /*<<< orphan*/  symtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_source_line ; 
 int /*<<< orphan*/  current_source_symtab ; 

struct symtab_and_line
get_current_source_symtab_and_line (void)
{
  struct symtab_and_line cursal;

  cursal.symtab = current_source_symtab;
  cursal.line = current_source_line;
  cursal.pc = 0;
  cursal.end = 0;
  
  return cursal;
}