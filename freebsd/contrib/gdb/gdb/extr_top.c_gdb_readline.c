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

/* Variables and functions */
 int EOF ; 
 int fgetc (scalar_t__) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ instream ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

char *
gdb_readline (char *prompt_arg)
{
  int c;
  char *result;
  int input_index = 0;
  int result_size = 80;

  if (prompt_arg)
    {
      /* Don't use a _filtered function here.  It causes the assumed
         character position to be off, since the newline we read from
         the user is not accounted for.  */
      fputs_unfiltered (prompt_arg, gdb_stdout);
      gdb_flush (gdb_stdout);
    }

  result = (char *) xmalloc (result_size);

  while (1)
    {
      /* Read from stdin if we are executing a user defined command.
         This is the right thing for prompt_for_continue, at least.  */
      c = fgetc (instream ? instream : stdin);

      if (c == EOF)
	{
	  if (input_index > 0)
	    /* The last line does not end with a newline.  Return it, and
	       if we are called again fgetc will still return EOF and
	       we'll return NULL then.  */
	    break;
	  xfree (result);
	  return NULL;
	}

      if (c == '\n')
#ifndef CRLF_SOURCE_FILES
	break;
#else
	{
	  if (input_index > 0 && result[input_index - 1] == '\r')
	    input_index--;
	  break;
	}
#endif

      result[input_index++] = c;
      while (input_index >= result_size)
	{
	  result_size *= 2;
	  result = (char *) xrealloc (result, result_size);
	}
    }

  result[input_index++] = '\0';
  return result;
}