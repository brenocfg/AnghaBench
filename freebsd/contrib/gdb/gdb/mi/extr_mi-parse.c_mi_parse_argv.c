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
struct mi_parse {char** argv; int argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeargv (char**) ; 
 scalar_t__ isspace (char) ; 
 char parse_escape (char**) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 void* xmalloc (int) ; 
 char** xrealloc (char**,int) ; 

__attribute__((used)) static void
mi_parse_argv (char *args, struct mi_parse *parse)
{
  char *chp = args;
  int argc = 0;
  char **argv = xmalloc ((argc + 1) * sizeof (char *));
  argv[argc] = NULL;
  while (1)
    {
      char *arg;
      /* skip leading white space */
      while (isspace (*chp))
	chp++;
      /* Three possibilities: EOF, quoted string, or other text. */
      switch (*chp)
	{
	case '\0':
	  parse->argv = argv;
	  parse->argc = argc;
	  return;
	case '"':
	  {
	    /* A quoted string. */
	    int len;
	    char *start = chp + 1;
	    /* Determine the buffer size. */
	    chp = start;
	    len = 0;
	    while (*chp != '\0' && *chp != '"')
	      {
		if (*chp == '\\')
		  {
		    chp++;
		    if (parse_escape (&chp) <= 0)
		      {
			/* Do not allow split lines or "\000" */
			freeargv (argv);
			return;
		      }
		  }
		else
		  chp++;
		len++;
	      }
	    /* Insist on a closing quote. */
	    if (*chp != '"')
	      {
		freeargv (argv);
		return;
	      }
	    /* Insist on trailing white space. */
	    if (chp[1] != '\0' && !isspace (chp[1]))
	      {
		freeargv (argv);
		return;
	      }
	    /* create the buffer. */
	    arg = xmalloc ((len + 1) * sizeof (char));
	    /* And copy the characters in. */
	    chp = start;
	    len = 0;
	    while (*chp != '\0' && *chp != '"')
	      {
		if (*chp == '\\')
		  {
		    chp++;
		    arg[len] = parse_escape (&chp);
		  }
		else
		  arg[len] = *chp++;
		len++;
	      }
	    arg[len] = '\0';
	    chp++;		/* that closing quote. */
	    break;
	  }
	default:
	  {
	    /* An unquoted string.  Accumulate all non blank
	       characters into a buffer. */
	    int len;
	    char *start = chp;
	    while (*chp != '\0' && !isspace (*chp))
	      {
		chp++;
	      }
	    len = chp - start;
	    arg = xmalloc ((len + 1) * sizeof (char));
	    strncpy (arg, start, len);
	    arg[len] = '\0';
	    break;
	  }
	}
      /* Append arg to argv. */
      argv = xrealloc (argv, (argc + 2) * sizeof (char *));
      argv[argc++] = arg;
      argv[argc] = NULL;
    }
}