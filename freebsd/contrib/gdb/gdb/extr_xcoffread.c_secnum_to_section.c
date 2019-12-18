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
struct objfile {int /*<<< orphan*/  obfd; } ;
struct find_targ_sec_arg {int targ_index; int* resultp; struct objfile* objfile; int /*<<< orphan*/ ** bfd_sect; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_targ_sec_arg*) ; 
 int /*<<< orphan*/  find_targ_sec ; 

__attribute__((used)) static int
secnum_to_section (int secnum, struct objfile *objfile)
{
  int off = SECT_OFF_TEXT (objfile);
  asection *sect = NULL;
  struct find_targ_sec_arg args;
  args.targ_index = secnum;
  args.resultp = &off;
  args.bfd_sect = &sect;
  args.objfile = objfile;
  bfd_map_over_sections (objfile->obfd, find_targ_sec, &args);
  return off;
}