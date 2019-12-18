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
struct objfile {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct general_symbol_info {int /*<<< orphan*/  section; int /*<<< orphan*/  bfd_section; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_BFD_SECTION (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_SECTION (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct objfile*) ; 

__attribute__((used)) static void
fixup_section (struct general_symbol_info *ginfo, struct objfile *objfile)
{
  struct minimal_symbol *msym;
  msym = lookup_minimal_symbol (ginfo->name, NULL, objfile);

  if (msym)
    {
      ginfo->bfd_section = SYMBOL_BFD_SECTION (msym);
      ginfo->section = SYMBOL_SECTION (msym);
    }
}