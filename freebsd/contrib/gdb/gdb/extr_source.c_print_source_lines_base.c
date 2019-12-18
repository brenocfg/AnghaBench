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
struct symtab {char* filename; int nlines; int /*<<< orphan*/ * line_charpos; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FDOPEN_MODE ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int current_source_line ; 
 struct symtab* current_source_symtab ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,int /*<<< orphan*/ ) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_source_lines (struct symtab*,int) ; 
 int first_line_listed ; 
 int last_line_listed ; 
 int last_source_error ; 
 struct symtab* last_source_visited ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open_source_file (struct symtab*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ui_out_test_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ui_source_list ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_source_lines_base (struct symtab *s, int line, int stopline, int noerror)
{
  int c;
  int desc;
  FILE *stream;
  int nlines = stopline - line;

  /* Regardless of whether we can open the file, set current_source_symtab. */
  current_source_symtab = s;
  current_source_line = line;
  first_line_listed = line;

  /* If printing of source lines is disabled, just print file and line number */
  if (ui_out_test_flags (uiout, ui_source_list))
    {
      /* Only prints "No such file or directory" once */
      if ((s != last_source_visited) || (!last_source_error))
	{
	  last_source_visited = s;
	  desc = open_source_file (s);
	}
      else
	{
	  desc = last_source_error;
	  noerror = 1;
	}
    }
  else
    {
      desc = -1;
      noerror = 1;
    }

  if (desc < 0)
    {
      last_source_error = desc;

      if (!noerror)
	{
	  char *name = alloca (strlen (s->filename) + 100);
	  sprintf (name, "%d\t%s", line, s->filename);
	  print_sys_errmsg (name, errno);
	}
      else
	ui_out_field_int (uiout, "line", line);
      ui_out_text (uiout, "\tin ");
      ui_out_field_string (uiout, "file", s->filename);
      ui_out_text (uiout, "\n");

      return;
    }

  last_source_error = 0;

  if (s->line_charpos == 0)
    find_source_lines (s, desc);

  if (line < 1 || line > s->nlines)
    {
      close (desc);
      error ("Line number %d out of range; %s has %d lines.",
	     line, s->filename, s->nlines);
    }

  if (lseek (desc, s->line_charpos[line - 1], 0) < 0)
    {
      close (desc);
      perror_with_name (s->filename);
    }

  stream = fdopen (desc, FDOPEN_MODE);
  clearerr (stream);

  while (nlines-- > 0)
    {
      char buf[20];

      c = fgetc (stream);
      if (c == EOF)
	break;
      last_line_listed = current_source_line;
      sprintf (buf, "%d\t", current_source_line++);
      ui_out_text (uiout, buf);
      do
	{
	  if (c < 040 && c != '\t' && c != '\n' && c != '\r')
	    {
	      sprintf (buf, "^%c", c + 0100);
	      ui_out_text (uiout, buf);
	    }
	  else if (c == 0177)
	    ui_out_text (uiout, "^?");
#ifdef CRLF_SOURCE_FILES
	  else if (c == '\r')
	    {
	      /* Skip a \r character, but only before a \n.  */
	      int c1 = fgetc (stream);

	      if (c1 != '\n')
		printf_filtered ("^%c", c + 0100);
	      if (c1 != EOF)
		ungetc (c1, stream);
	    }
#endif
	  else
	    {
	      sprintf (buf, "%c", c);
	      ui_out_text (uiout, buf);
	    }
	}
      while (c != '\n' && (c = fgetc (stream)) >= 0);
    }

  fclose (stream);
}