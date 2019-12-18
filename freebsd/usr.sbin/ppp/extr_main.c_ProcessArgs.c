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
struct switches {int mode; int unit; int nat; int quiet; int fg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_START ; 
 int /*<<< orphan*/  LogWARN ; 
 int Nam2mode (char*) ; 
#define  PHYS_ALL 129 
 scalar_t__ PHYS_AUTO ; 
 int PHYS_FOREGROUND ; 
 int PHYS_INTERACTIVE ; 
#define  PHYS_NONE 128 
 int /*<<< orphan*/  Usage () ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (struct switches*,char,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ProcessArgs(int argc, char **argv, struct switches *sw)
{
  int optc, newmode, arg;
  char *cp;

  optc = 0;
  memset(sw, '\0', sizeof *sw);
  sw->mode = PHYS_INTERACTIVE;
  sw->unit = -1;

  for (arg = 1; arg < argc && *argv[arg] == '-'; arg++, optc++) {
    cp = argv[arg] + 1;
    newmode = Nam2mode(cp);
    switch (newmode) {
      case PHYS_NONE:
        if (strcmp(cp, "nat") == 0) {
#ifdef NONAT
          log_Printf(LogWARN, "%s ignored: NAT is compiled out\n", argv[arg]);
#else
          sw->nat = 1;
#endif
          optc--;			/* this option isn't exclusive */
        } else if (strcmp(cp, "alias") == 0) {
#ifdef NONAT
          log_Printf(LogWARN, "%s ignored: NAT is compiled out\n", argv[arg]);
          fprintf(stderr, "%s ignored: NAT is compiled out\n", argv[arg]);
#else
          log_Printf(LogWARN, "%s is deprecated\n", argv[arg]);
          fprintf(stderr, "%s is deprecated\n", argv[arg]);
          sw->nat = 1;
#endif
          optc--;			/* this option isn't exclusive */
        } else if (strncmp(cp, "unit", 4) == 0) {
          optc--;			/* this option isn't exclusive */
          if (cp[4] == '\0') {
            optc--;			/* nor is the argument */
            if (++arg == argc) {
              fprintf(stderr, "-unit: Expected unit number\n");
              Usage();
            } else
              sw->unit = atoi(argv[arg]);
          } else
            sw->unit = atoi(cp + 4);
        } else if (strcmp(cp, "quiet") == 0) {
          sw->quiet = 1;
          optc--;			/* this option isn't exclusive */
        } else
          Usage();
        break;

      case PHYS_ALL:
        Usage();
        break;

      default:
        sw->mode = newmode;
        if (newmode == PHYS_FOREGROUND)
          sw->fg = 1;
    }
  }

  if (optc > 1) {
    fprintf(stderr, "You may specify only one mode.\n");
    exit(EX_START);
  }

  if (sw->mode == PHYS_AUTO && arg == argc) {
    fprintf(stderr, "A system must be specified in auto mode.\n");
    exit(EX_START);
  }

  return arg;		/* Don't SetLabel yet ! */
}