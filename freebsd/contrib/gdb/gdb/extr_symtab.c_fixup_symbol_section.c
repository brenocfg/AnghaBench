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
struct symbol {int /*<<< orphan*/  ginfo; } ;
struct objfile {int dummy; } ;

/* Variables and functions */
 scalar_t__ SYMBOL_BFD_SECTION (struct symbol*) ; 
 int /*<<< orphan*/  fixup_section (int /*<<< orphan*/ *,struct objfile*) ; 

struct symbol *
fixup_symbol_section (struct symbol *sym, struct objfile *objfile)
{
  if (!sym)
    return NULL;

  if (SYMBOL_BFD_SECTION (sym))
    return sym;

  fixup_section (&sym->ginfo, objfile);

  return sym;
}