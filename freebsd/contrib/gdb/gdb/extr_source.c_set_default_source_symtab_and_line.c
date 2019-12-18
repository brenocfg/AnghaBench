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
struct symtab_and_line {int dummy; } ;

/* Variables and functions */
 scalar_t__ current_source_symtab ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  have_full_symbols () ; 
 int /*<<< orphan*/  have_partial_symbols () ; 
 int /*<<< orphan*/  select_source_symtab (int /*<<< orphan*/ ) ; 

void
set_default_source_symtab_and_line (void)
{
  struct symtab_and_line cursal;

  if (!have_full_symbols () && !have_partial_symbols ())
    error ("No symbol table is loaded.  Use the \"file\" command.");

  /* Pull in a current source symtab if necessary */
  if (current_source_symtab == 0)
    select_source_symtab (0);
}