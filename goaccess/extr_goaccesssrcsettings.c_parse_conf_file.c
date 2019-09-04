#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* iconfigfile; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int /*<<< orphan*/  MAX_LINE_CONF ; 
 int /*<<< orphan*/  append_to_argv (int*,scalar_t__*,char*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_config_file_path () ; 
 scalar_t__ in_ignore_cmd_opts (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int nargc ; 
 scalar_t__ nargv ; 
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strpbrk (char*,char*) ; 
 size_t strspn (char*,char*) ; 
 char* trim_str (char*) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrdup (char*) ; 

int
parse_conf_file (int *argc, char ***argv)
{
  char line[MAX_LINE_CONF + 1];
  char *path = NULL, *val, *opt, *p;
  FILE *file;
  int i, n = 0;
  size_t idx;

  /* assumes program name is on argv[0], though, it is not guaranteed */
  append_to_argv (&nargc, &nargv, xstrdup ((char *) *argv[0]));

  /* determine which config file to open, default or custom */
  path = get_config_file_path ();
  if (path == NULL)
    return ENOENT;

  /* could not open conf file, if so prompt conf dialog */
  if ((file = fopen (path, "r")) == NULL) {
    free (path);
    return ENOENT;
  }

  while (fgets (line, sizeof line, file) != NULL) {
    while (line[0] == ' ' || line[0] == '\t')
      memmove (line, line + 1, strlen (line));
    n++;
    if (line[0] == '\n' || line[0] == '\r' || line[0] == '#')
      continue;

    /* key */
    idx = strcspn (line, " \t");
    if (strlen (line) == idx)
      FATAL ("Malformed config key at line: %d", n);

    line[idx] = '\0';

    /* make old config options backwards compatible by
     * substituting underscores with dashes */
    while ((p = strpbrk (line, "_")) != NULL)
      *p = '-';

    /* Ignore the following options when reading the config file */
    if (in_ignore_cmd_opts (line))
      continue;

    /* value */
    val = line + (idx + 1);
    idx = strspn (val, " \t");
    if (strlen (line) == idx)
      FATAL ("Malformed config value at line: %d", n);
    val = val + idx;
    val = trim_str (val);

    if (strcmp ("false", val) == 0)
      continue;

    /* set it as command line options */
    opt = xmalloc (snprintf (NULL, 0, "--%s", line) + 1);
    sprintf (opt, "--%s", line);

    append_to_argv (&nargc, &nargv, opt);
    if (strcmp ("true", val) != 0)
      append_to_argv (&nargc, &nargv, xstrdup (val));
  }

  /* give priority to command line arguments */
  for (i = 1; i < *argc; i++)
    append_to_argv (&nargc, &nargv, xstrdup ((char *) (*argv)[i]));

  *argc = nargc;
  *argv = (char **) nargv;

  fclose (file);

  if (conf.iconfigfile == NULL)
    conf.iconfigfile = xstrdup (path);

  free (path);
  return 0;
}