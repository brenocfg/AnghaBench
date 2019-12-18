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
struct symtab {char* fullname; scalar_t__ line_charpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  find_source_lines (struct symtab*,int) ; 
 int open_source_file (struct symtab*) ; 

__attribute__((used)) static int
get_filename_and_charpos (struct symtab *s, char **fullname)
{
  int desc, linenums_changed = 0;

  desc = open_source_file (s);
  if (desc < 0)
    {
      if (fullname)
	*fullname = NULL;
      return 0;
    }
  if (fullname)
    *fullname = s->fullname;
  if (s->line_charpos == 0)
    linenums_changed = 1;
  if (linenums_changed)
    find_source_lines (s, desc);
  close (desc);
  return linenums_changed;
}