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
struct prompt {int dummy; } ;
struct datalink {int dummy; } ;
struct bundle {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CTRL_INCLUDE 128 
 int /*<<< orphan*/  DecodeCtrlCommand (char*,char*) ; 
 char* GetLabel (char*,char*,int) ; 
 int /*<<< orphan*/ * ID0fopen (char*,char*) ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  LogCOMMAND ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXARGS ; 
 int PATH_MAX ; 
 char* PPP_CONFDIR ; 
 int SYSTEM_EXEC ; 
 int SYSTEM_EXISTS ; 
 int command_Expand_Interpret (char*,int,char**,int) ; 
 int /*<<< orphan*/  command_Run (struct bundle*,int,char const* const*,struct prompt*,char const*,struct datalink*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int issep (char) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 struct prompt* log_PromptContext ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strip (char*) ; 
 int strlen (char*) ; 
 int xgets (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ReadSystem(struct bundle *bundle, const char *name, const char *file,
           struct prompt *prompt, struct datalink *cx, int how)
{
  FILE *fp;
  char *cp;
  int n, len;
  char line[LINE_LEN];
  char filename[PATH_MAX];
  int linenum;
  int argc;
  char *argv[MAXARGS];
  int allowcmd;
  int indent;
  char arg[LINE_LEN];
  struct prompt *op;

  if (*file == '/')
    snprintf(filename, sizeof filename, "%s", file);
  else
    snprintf(filename, sizeof filename, "%s/%s", PPP_CONFDIR, file);
  fp = ID0fopen(filename, "r");
  if (fp == NULL) {
    log_Printf(LogDEBUG, "ReadSystem: Can't open %s.\n", filename);
    return -2;
  }
  log_Printf(LogDEBUG, "ReadSystem: Checking %s (%s).\n", name, filename);

  linenum = 0;
  while ((n = xgets(line, sizeof line, fp))) {
    linenum += n;
    if (issep(*line))
      continue;

    cp = strip(line);

    switch (*cp) {
    case '\0':			/* empty/comment */
      break;

    case '!':
      switch (DecodeCtrlCommand(cp+1, arg)) {
      case CTRL_INCLUDE:
        log_Printf(LogCOMMAND, "%s: Including \"%s\"\n", filename, arg);
        n = ReadSystem(bundle, name, arg, prompt, cx, how);
        log_Printf(LogCOMMAND, "%s: Done include of \"%s\"\n", filename, arg);
        if (!n) {
          fclose(fp);
          return 0;	/* got it */
        }
        break;
      default:
        log_Printf(LogWARN, "%s: %s: Invalid command\n", filename, cp);
        break;
      }
      break;

    default:
      if ((cp = GetLabel(cp, filename, linenum)) == NULL)
        continue;

      if (strcmp(cp, name) == 0) {
        /* We're in business */
        if (how == SYSTEM_EXISTS) {
          fclose(fp);
	  return 0;
	}
	while ((n = xgets(line, sizeof line, fp))) {
          linenum += n;
          indent = issep(*line);
          cp = strip(line);

          if (*cp == '\0')			/* empty / comment */
            continue;

          if (!indent) {			/* start of next section */
            if (*cp != '!' && how == SYSTEM_EXEC)
              cp = GetLabel(cp, filename, linenum);
            break;
          }

          len = strlen(cp);
          if ((argc = command_Expand_Interpret(cp, len, argv, cp - line)) < 0)
            log_Printf(LogWARN, "%s: %d: Syntax error\n", filename, linenum);
          else {
            allowcmd = argc > 0 && !strcasecmp(argv[0], "allow");
            if ((how != SYSTEM_EXEC && allowcmd) ||
                (how == SYSTEM_EXEC && !allowcmd)) {
              /*
               * Disable any context so that warnings are given to everyone,
               * including syslog.
               */
              op = log_PromptContext;
              log_PromptContext = NULL;
	      command_Run(bundle, argc, (char const *const *)argv, prompt,
                          name, cx);
              log_PromptContext = op;
            }
          }
        }

	fclose(fp);  /* everything read - get out */
	return 0;
      }
      break;
    }
  }
  fclose(fp);
  return -1;
}