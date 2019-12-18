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
 int /*<<< orphan*/  LogWARN ; 
 int MAXARGS ; 
 int MakeArgs (char*,char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_REDUCE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
GetLabel(char *line, const char *filename, int linenum)
{
  char *argv[MAXARGS];
  int argc, len;

  argc = MakeArgs(line, argv, MAXARGS, PARSE_REDUCE);

  if (argc == 2 && !strcmp(argv[1], ":"))
    return argv[0];

  if (argc != 1 || (len = strlen(argv[0])) < 2 || argv[0][len-1] != ':') {
      log_Printf(LogWARN, "Bad label in %s (line %d) - missing colon\n",
                 filename, linenum);
      return NULL;
  }
  argv[0][len-1] = '\0';	/* Lose the ':' */

  return argv[0];
}