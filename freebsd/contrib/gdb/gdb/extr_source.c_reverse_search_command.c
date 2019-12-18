#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nlines; int /*<<< orphan*/  filename; int /*<<< orphan*/ * line_charpos; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FDOPEN_MODE ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  current_source_line ; 
 TYPE_1__* current_source_symtab ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_source_lines (TYPE_1__*,int) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int last_line_listed ; 
 int lines_to_list ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int open_source_file (TYPE_1__*) ; 
 int /*<<< orphan*/  perror_with_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_source_lines (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 scalar_t__ re_comp (char*) ; 
 scalar_t__ re_exec (char*) ; 
 int /*<<< orphan*/  select_source_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_internalvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reverse_search_command (char *regex, int from_tty)
{
  int c;
  int desc;
  FILE *stream;
  int line;
  char *msg;

  line = last_line_listed - 1;

  msg = (char *) re_comp (regex);
  if (msg)
    error ("%s", msg);

  if (current_source_symtab == 0)
    select_source_symtab (0);

  desc = open_source_file (current_source_symtab);
  if (desc < 0)
    perror_with_name (current_source_symtab->filename);

  if (current_source_symtab->line_charpos == 0)
    find_source_lines (current_source_symtab, desc);

  if (line < 1 || line > current_source_symtab->nlines)
    {
      close (desc);
      error ("Expression not found");
    }

  if (lseek (desc, current_source_symtab->line_charpos[line - 1], 0) < 0)
    {
      close (desc);
      perror_with_name (current_source_symtab->filename);
    }

  stream = fdopen (desc, FDOPEN_MODE);
  clearerr (stream);
  while (line > 1)
    {
/* FIXME!!!  We walk right off the end of buf if we get a long line!!! */
      char buf[4096];		/* Should be reasonable??? */
      char *p = buf;

      c = getc (stream);
      if (c == EOF)
	break;
      do
	{
	  *p++ = c;
	}
      while (c != '\n' && (c = getc (stream)) >= 0);

#ifdef CRLF_SOURCE_FILES
      /* Remove the \r, if any, at the end of the line, otherwise
         regular expressions that end with $ or \n won't work.  */
      if (p - buf > 1 && p[-2] == '\r')
	{
	  p--;
	  p[-1] = '\n';
	}
#endif

      /* We now have a source line in buf; null terminate and match.  */
      *p = 0;
      if (re_exec (buf) > 0)
	{
	  /* Match! */
	  fclose (stream);
	  print_source_lines (current_source_symtab, line, line + 1, 0);
	  set_internalvar (lookup_internalvar ("_"),
			   value_from_longest (builtin_type_int,
					       (LONGEST) line));
	  current_source_line = max (line - lines_to_list / 2, 1);
	  return;
	}
      line--;
      if (fseek (stream, current_source_symtab->line_charpos[line - 1], 0) < 0)
	{
	  fclose (stream);
	  perror_with_name (current_source_symtab->filename);
	}
    }

  printf_filtered ("Expression not found\n");
  fclose (stream);
  return;
}