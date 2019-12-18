#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct switches {scalar_t__ mode; int /*<<< orphan*/  fg; int /*<<< orphan*/  quiet; scalar_t__ nat; int /*<<< orphan*/  unit; } ;
struct stat {int st_mode; } ;
struct prompt {struct bundle* bundle; } ;
struct TYPE_6__ {int fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  peer_range; } ;
struct TYPE_8__ {TYPE_2__ cfg; } ;
struct TYPE_9__ {TYPE_3__ ipcp; } ;
struct bundle {TYPE_1__ notify; TYPE_5__* iface; TYPE_4__ ncp; scalar_t__ NatEnabled; } ;
typedef  int pid_t ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  AbortProgram (int) ; 
 int BGPid ; 
 int /*<<< orphan*/  BringDownServer ; 
 char* CONFFILE ; 
 int /*<<< orphan*/  CheckLabel (char*,struct prompt*,scalar_t__) ; 
 int /*<<< orphan*/  CloseConnection ; 
 int /*<<< orphan*/  CloseSession ; 
 int /*<<< orphan*/  DoLoop (struct bundle*) ; 
#define  EX_NORMAL 130 
#define  EX_RECONNECT 129 
#define  EX_REDIAL 128 
 int EX_SOCK ; 
 int EX_START ; 
 int /*<<< orphan*/  ID0init () ; 
 scalar_t__ ID0realuid () ; 
 int /*<<< orphan*/  KillChild ; 
 int /*<<< orphan*/  LibAliasInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  OPT_IFACEALIAS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ PHYS_AUTO ; 
 scalar_t__ PHYS_BACKGROUND ; 
 scalar_t__ PHYS_DIRECT ; 
 scalar_t__ PHYS_INTERACTIVE ; 
 char* PPP_CONFDIR ; 
 int /*<<< orphan*/  PROMPT_STD ; 
 int ProcessArgs (int,char**,struct switches*) ; 
 int /*<<< orphan*/  RestartServer ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int S_IWOTH ; 
 struct bundle* SignalBundle ; 
 struct prompt* SignalPrompt ; 
 int /*<<< orphan*/  TUN_PREFIX ; 
 int /*<<< orphan*/  TerminalStop ; 
 char* _PATH_DEVNULL ; 
 char* _PATH_TTY ; 
 int /*<<< orphan*/  bundle_ChangedPID (struct bundle*) ; 
 struct bundle* bundle_Create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_LockTun (struct bundle*) ; 
 int /*<<< orphan*/  bundle_SetLabel (struct bundle*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  errno ; 
 char* ex_desc (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  la ; 
 int /*<<< orphan*/  log_Open (char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 char* mode2Nam (scalar_t__) ; 
 scalar_t__ ncprange_family (int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_enable (struct bundle*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  probe_Init () ; 
 struct prompt* prompt_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prompt_Destroy (struct prompt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prompt_Printf (struct prompt*,char*,...) ; 
 int /*<<< orphan*/  prompt_Required (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TtyCommandMode (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TtyInit (struct prompt*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  sig_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ system_Select (struct bundle*,char*,char*,struct prompt*,int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
  char *name;
  const char *lastlabel;
  int arg, holdfd[3], label;
  unsigned f;
  struct bundle *bundle;
  struct prompt *prompt;
  struct switches sw;

  probe_Init();

  /*
   * We open 3 descriptors to ensure that STDIN_FILENO, STDOUT_FILENO and
   * STDERR_FILENO are always open.  These are closed before DoLoop(),
   * but *after* we've avoided the possibility of erroneously closing
   * an important descriptor with close(STD{IN,OUT,ERR}_FILENO).
   */
  if ((holdfd[0] = open(_PATH_DEVNULL, O_RDWR)) == -1) {
    fprintf(stderr, "Cannot open %s !\n", _PATH_DEVNULL);
    return 2;
  }
  for (f = 1; f < sizeof holdfd / sizeof *holdfd; f++)
    holdfd[f] = dup(holdfd[0]);

  name = strrchr(argv[0], '/');
  log_Open(name ? name + 1 : argv[0]);

#ifndef NONAT
  la = LibAliasInit(NULL);
#endif
  label = ProcessArgs(argc, argv, &sw);

  /*
   * A FreeBSD & OpenBSD hack to dodge a bug in the tty driver that drops
   * output occasionally.... I must find the real reason some time.  To
   * display the dodgy behaviour, comment out this bit, make yourself a large
   * routing table and then run ppp in interactive mode.  The `show route'
   * command will drop chunks of data !!!
   */
  if (sw.mode == PHYS_INTERACTIVE) {
    close(STDIN_FILENO);
    if (open(_PATH_TTY, O_RDONLY) != STDIN_FILENO) {
      fprintf(stderr, "Cannot open %s for input !\n", _PATH_TTY);
      return 2;
    }
  }

  /* Allow output for the moment (except in direct mode) */
  if (sw.mode == PHYS_DIRECT)
    prompt = NULL;
  else
    SignalPrompt = prompt = prompt_Create(NULL, NULL, PROMPT_STD);

  ID0init();
  if (ID0realuid() != 0) {
    char conf[200], *ptr;

    snprintf(conf, sizeof conf, "%s/%s", PPP_CONFDIR, CONFFILE);
    do {
      struct stat sb;

      if (stat(conf, &sb) == 0 && sb.st_mode & S_IWOTH) {
        log_Printf(LogALERT, "ppp: Access violation: Please protect %s\n",
                   conf);
        return -1;
      }
      ptr = conf + strlen(conf)-2;
      while (ptr > conf && *ptr != '/')
        *ptr-- = '\0';
    } while (ptr >= conf);
  }

  if (label < argc)
    for (arg = label; arg < argc; arg++)
      CheckLabel(argv[arg], prompt, sw.mode);
  else
    CheckLabel("default", prompt, sw.mode);

  if (!sw.quiet)
    prompt_Printf(prompt, "Working in %s mode\n", mode2Nam(sw.mode));

  if ((bundle = bundle_Create(TUN_PREFIX, sw.mode, sw.unit)) == NULL)
    return EX_START;

  /* NOTE:  We may now have changed argv[1] via a ``set proctitle'' */

  SignalBundle = bundle;
  bundle->NatEnabled = sw.nat;
  if (sw.nat)
    opt_enable(bundle, OPT_IFACEALIAS);

  if (system_Select(bundle, "default", CONFFILE, prompt, NULL) < 0)
    prompt_Printf(prompt, "Warning: No default entry found in config file.\n");

  sig_signal(SIGHUP, CloseSession);
  sig_signal(SIGTERM, CloseSession);
  sig_signal(SIGINT, CloseConnection);
  sig_signal(SIGQUIT, CloseSession);
  sig_signal(SIGALRM, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);

  if (sw.mode == PHYS_INTERACTIVE)
    sig_signal(SIGTSTP, TerminalStop);

  sig_signal(SIGUSR1, RestartServer);
  sig_signal(SIGUSR2, BringDownServer);

  lastlabel = argv[argc - 1];
  for (arg = label; arg < argc; arg++) {
    /* In case we use LABEL or ``set enddisc label'' */
    bundle_SetLabel(bundle, lastlabel);
    system_Select(bundle, argv[arg], CONFFILE, prompt, NULL);
  }

  if (label < argc)
    /* In case the last label did a ``load'' */
    bundle_SetLabel(bundle, lastlabel);

  if (sw.mode == PHYS_AUTO &&
      ncprange_family(&bundle->ncp.ipcp.cfg.peer_range) == AF_UNSPEC) {
    prompt_Printf(prompt, "You must ``set ifaddr'' with a peer address "
                  "in auto mode.\n");
    AbortProgram(EX_START);
  }

  if (prompt) {
    prompt->bundle = bundle;	/* couldn't do it earlier */
    if (!sw.quiet)
      prompt_Printf(prompt, "Using interface: %s\n", bundle->iface->name);
  } 

  if (sw.mode != PHYS_INTERACTIVE) {
    if (sw.mode != PHYS_DIRECT) {
      if (!sw.fg) {
        int bgpipe[2];
        pid_t bgpid;

        if (sw.mode == PHYS_BACKGROUND && pipe(bgpipe)) {
          log_Printf(LogERROR, "pipe: %s\n", strerror(errno));
	  AbortProgram(EX_SOCK);
        }

        bgpid = fork();
        if (bgpid == -1) {
	  log_Printf(LogERROR, "fork: %s\n", strerror(errno));
	  AbortProgram(EX_SOCK);
        }

        if (bgpid) {
	  char c = EX_NORMAL;
          int ret;

	  if (sw.mode == PHYS_BACKGROUND) {
	    close(bgpipe[1]);
	    BGPid = bgpid;
            /* If we get a signal, kill the child */
            signal(SIGHUP, KillChild);
            signal(SIGTERM, KillChild);
            signal(SIGINT, KillChild);
            signal(SIGQUIT, KillChild);

	    /* Wait for our child to close its pipe before we exit */
            while ((ret = read(bgpipe[0], &c, 1)) == 1) {
              switch (c) {
                case EX_NORMAL:
                  if (!sw.quiet) {
	            prompt_Printf(prompt, "PPP enabled\n");
	            log_Printf(LogPHASE, "Parent: PPP enabled\n");
                  }
	          break;
                case EX_REDIAL:
                  if (!sw.quiet)
	            prompt_Printf(prompt, "Attempting redial\n");
                  continue;
                case EX_RECONNECT:
                  if (!sw.quiet)
	            prompt_Printf(prompt, "Attempting reconnect\n");
                  continue;
	        default:
	          prompt_Printf(prompt, "Child failed (%s)\n",
                                ex_desc((int)c));
	          log_Printf(LogPHASE, "Parent: Child failed (%s)\n",
		             ex_desc((int) c));
	      }
	      break;
            }
            if (ret != 1) {
	      prompt_Printf(prompt, "Child exit, no status.\n");
	      log_Printf(LogPHASE, "Parent: Child exit, no status.\n");
	    }
	    close(bgpipe[0]);
	  }
	  return c;
        } else if (sw.mode == PHYS_BACKGROUND) {
	  close(bgpipe[0]);
          bundle->notify.fd = bgpipe[1];
        }

        bundle_ChangedPID(bundle);
        bundle_LockTun(bundle);	/* we have a new pid */
      }

      /* -auto, -dedicated, -ddial, -foreground & -background */
      prompt_Destroy(prompt, 0);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);
      close(STDIN_FILENO);
      if (!sw.fg)
        setsid();
    } else {
      /*
       * -direct - STDIN_FILENO gets used by physical_Open.  STDOUT_FILENO
       * *may* get used in exec/pipe mode.
       */
      prompt_TtyInit(NULL);
      close(STDERR_FILENO);
    }
  } else {
    /* -interactive */
    close(STDERR_FILENO);
    prompt_TtyInit(prompt);
    prompt_TtyCommandMode(prompt);
    prompt_Required(prompt);
  }

  /* We can get rid of these now */
  for (f = 0; f < sizeof holdfd / sizeof *holdfd; f++)
    close(holdfd[f]);

  log_Printf(LogPHASE, "PPP Started (%s mode).\n", mode2Nam(sw.mode));
  DoLoop(bundle);
  AbortProgram(EX_NORMAL);

  return EX_NORMAL;
}