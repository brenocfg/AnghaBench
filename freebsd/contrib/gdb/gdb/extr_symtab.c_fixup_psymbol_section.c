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
struct partial_symbol {int /*<<< orphan*/  ginfo; } ;
struct objfile {int dummy; } ;

/* Variables and functions */
 scalar_t__ SYMBOL_BFD_SECTION (struct partial_symbol*) ; 
 int /*<<< orphan*/  fixup_section (int /*<<< orphan*/ *,struct objfile*) ; 

struct partial_symbol *
fixup_psymbol_section (struct partial_symbol *psym, struct objfile *objfile)
{
  if (!psym)
    return NULL;

  if (SYMBOL_BFD_SECTION (psym))
    return psym;

  fixup_section (&psym->ginfo, objfile);

  return psym;
}