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
struct symtab {scalar_t__ fullname; int nlines; int /*<<< orphan*/ * line_charpos; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  annotate_source (scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int current_source_line ; 
 struct symtab* current_source_symtab ; 
 int first_line_listed ; 
 int /*<<< orphan*/  get_filename_and_charpos (struct symtab*,char**) ; 
 int last_line_listed ; 

int
identify_source_line (struct symtab *s, int line, int mid_statement,
		      CORE_ADDR pc)
{
  if (s->line_charpos == 0)
    get_filename_and_charpos (s, (char **) NULL);
  if (s->fullname == 0)
    return 0;
  if (line > s->nlines)
    /* Don't index off the end of the line_charpos array.  */
    return 0;
  annotate_source (s->fullname, line, s->line_charpos[line - 1],
		   mid_statement, pc);

  current_source_line = line;
  first_line_listed = line;
  last_line_listed = line;
  current_source_symtab = s;
  return 1;
}