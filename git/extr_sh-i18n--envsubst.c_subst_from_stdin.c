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
 int /*<<< orphan*/  all_variables ; 
 int do_getc () ; 
 int /*<<< orphan*/  do_ungetc (int) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  sorted_string_list_member (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  variables_set ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
subst_from_stdin (void)
{
  static char *buffer;
  static size_t bufmax;
  static size_t buflen;
  int c;

  for (;;)
    {
      c = do_getc ();
      if (c == EOF)
	break;
      /* Look for $VARIABLE or ${VARIABLE}.  */
      if (c == '$')
	{
	  unsigned short int opening_brace = 0;
	  unsigned short int closing_brace = 0;

	  c = do_getc ();
	  if (c == '{')
	    {
	      opening_brace = 1;
	      c = do_getc ();
	    }
	  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
	    {
	      unsigned short int valid;

	      /* Accumulate the VARIABLE in buffer.  */
	      buflen = 0;
	      do
		{
		  if (buflen >= bufmax)
		    {
		      bufmax = 2 * bufmax + 10;
		      buffer = xrealloc (buffer, bufmax);
		    }
		  buffer[buflen++] = c;

		  c = do_getc ();
		}
	      while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		     || (c >= '0' && c <= '9') || c == '_');

	      if (opening_brace)
		{
		  if (c == '}')
		    {
		      closing_brace = 1;
		      valid = 1;
		    }
		  else
		    {
		      valid = 0;
		      do_ungetc (c);
		    }
		}
	      else
		{
		  valid = 1;
		  do_ungetc (c);
		}

	      if (valid)
		{
		  /* Terminate the variable in the buffer.  */
		  if (buflen >= bufmax)
		    {
		      bufmax = 2 * bufmax + 10;
		      buffer = xrealloc (buffer, bufmax);
		    }
		  buffer[buflen] = '\0';

		  /* Test whether the variable shall be substituted.  */
		  if (!all_variables
		      && !sorted_string_list_member (&variables_set, buffer))
		    valid = 0;
		}

	      if (valid)
		{
		  /* Substitute the variable's value from the environment.  */
		  const char *env_value = getenv (buffer);

		  if (env_value != NULL)
		    fputs (env_value, stdout);
		}
	      else
		{
		  /* Perform no substitution at all.  Since the buffered input
		     contains no other '$' than at the start, we can just
		     output all the buffered contents.  */
		  putchar ('$');
		  if (opening_brace)
		    putchar ('{');
		  fwrite (buffer, buflen, 1, stdout);
		  if (closing_brace)
		    putchar ('}');
		}
	    }
	  else
	    {
	      do_ungetc (c);
	      putchar ('$');
	      if (opening_brace)
		putchar ('{');
	    }
	}
      else
	putchar (c);
    }
}