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
struct stat {int st_mode; } ;

/* Variables and functions */
 char DIRNAME_SEPARATOR ; 
 scalar_t__ IS_ABSOLUTE_PATH (char*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 char* SLASH_STRING ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 char* concat (char*,char*,char*,...) ; 
 char* current_directory ; 
 int errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/  (*) (char*),char*) ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int) ; 
 char* savestring (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,unsigned int) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

void
add_path (char *dirname, char **which_path, int parse_separators)
{
  char *old = *which_path;
  int prefix = 0;

  if (dirname == 0)
    return;

  dirname = xstrdup (dirname);
  make_cleanup (xfree, dirname);

  do
    {
      char *name = dirname;
      char *p;
      struct stat st;

      {
	char *separator = NULL;
	char *space = NULL;
	char *tab = NULL;

	if (parse_separators)
	  {
	    separator = strchr (name, DIRNAME_SEPARATOR);
	    space = strchr (name, ' ');
	    tab = strchr (name, '\t');
	  }

	if (separator == 0 && space == 0 && tab == 0)
	  p = dirname = name + strlen (name);
	else
	  {
	    p = 0;
	    if (separator != 0 && (p == 0 || separator < p))
	      p = separator;
	    if (space != 0 && (p == 0 || space < p))
	      p = space;
	    if (tab != 0 && (p == 0 || tab < p))
	      p = tab;
	    dirname = p + 1;
	    while (*dirname == DIRNAME_SEPARATOR
		   || *dirname == ' '
		   || *dirname == '\t')
	      ++dirname;
	  }
      }

      if (!(IS_DIR_SEPARATOR (*name) && p <= name + 1)	 /* "/" */
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      /* On MS-DOS and MS-Windows, h:\ is different from h: */
	  && !(p == name + 3 && name[1] == ':') 	 /* "d:/" */
#endif
	  && IS_DIR_SEPARATOR (p[-1]))
	/* Sigh. "foo/" => "foo" */
	--p;
      *p = '\0';

      while (p > name && p[-1] == '.')
	{
	  if (p - name == 1)
	    {
	      /* "." => getwd ().  */
	      name = current_directory;
	      goto append;
	    }
	  else if (p > name + 1 && IS_DIR_SEPARATOR (p[-2]))
	    {
	      if (p - name == 2)
		{
		  /* "/." => "/".  */
		  *--p = '\0';
		  goto append;
		}
	      else
		{
		  /* "...foo/." => "...foo".  */
		  p -= 2;
		  *p = '\0';
		  continue;
		}
	    }
	  else
	    break;
	}

      if (name[0] == '~')
	name = tilde_expand (name);
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      else if (IS_ABSOLUTE_PATH (name) && p == name + 2) /* "d:" => "d:." */
	name = concat (name, ".", NULL);
#endif
      else if (!IS_ABSOLUTE_PATH (name) && name[0] != '$')
	name = concat (current_directory, SLASH_STRING, name, NULL);
      else
	name = savestring (name, p - name);
      make_cleanup (xfree, name);

      /* Unless it's a variable, check existence.  */
      if (name[0] != '$')
	{
	  /* These are warnings, not errors, since we don't want a
	     non-existent directory in a .gdbinit file to stop processing
	     of the .gdbinit file.

	     Whether they get added to the path is more debatable.  Current
	     answer is yes, in case the user wants to go make the directory
	     or whatever.  If the directory continues to not exist/not be
	     a directory/etc, then having them in the path should be
	     harmless.  */
	  if (stat (name, &st) < 0)
	    {
	      int save_errno = errno;
	      fprintf_unfiltered (gdb_stderr, "Warning: ");
	      print_sys_errmsg (name, save_errno);
	    }
	  else if ((st.st_mode & S_IFMT) != S_IFDIR)
	    warning ("%s is not a directory.", name);
	}

    append:
      {
	unsigned int len = strlen (name);

	p = *which_path;
	while (1)
	  {
	    /* FIXME: strncmp loses in interesting ways on MS-DOS and
	       MS-Windows because of case-insensitivity and two different
	       but functionally identical slash characters.  We need a
	       special filesystem-dependent file-name comparison function.

	       Actually, even on Unix I would use realpath() or its work-
	       alike before comparing.  Then all the code above which
	       removes excess slashes and dots could simply go away.  */
	    if (!strncmp (p, name, len)
		&& (p[len] == '\0' || p[len] == DIRNAME_SEPARATOR))
	      {
		/* Found it in the search path, remove old copy */
		if (p > *which_path)
		  p--;		/* Back over leading separator */
		if (prefix > p - *which_path)
		  goto skip_dup;	/* Same dir twice in one cmd */
		strcpy (p, &p[len + 1]);	/* Copy from next \0 or  : */
	      }
	    p = strchr (p, DIRNAME_SEPARATOR);
	    if (p != 0)
	      ++p;
	    else
	      break;
	  }
	if (p == 0)
	  {
	    char tinybuf[2];

	    tinybuf[0] = DIRNAME_SEPARATOR;
	    tinybuf[1] = '\0';

	    /* If we have already tacked on a name(s) in this command, be sure they stay 
	       on the front as we tack on some more.  */
	    if (prefix)
	      {
		char *temp, c;

		c = old[prefix];
		old[prefix] = '\0';
		temp = concat (old, tinybuf, name, NULL);
		old[prefix] = c;
		*which_path = concat (temp, "", &old[prefix], NULL);
		prefix = strlen (temp);
		xfree (temp);
	      }
	    else
	      {
		*which_path = concat (name, (old[0] ? tinybuf : old), old, NULL);
		prefix = strlen (name);
	      }
	    xfree (old);
	    old = *which_path;
	  }
      }
    skip_dup:;
    }
  while (*dirname != '\0');
}