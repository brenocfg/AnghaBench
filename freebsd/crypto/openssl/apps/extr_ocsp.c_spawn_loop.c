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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  OPENSSL_free (scalar_t__*) ; 
 int /*<<< orphan*/  RAND_poll () ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ WCOREDUMP (int) ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__* app_malloc (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  killall (int,scalar_t__*) ; 
 int multi ; 
 int /*<<< orphan*/  noteterm ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog ; 
 scalar_t__ setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 long strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 long termsig ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spawn_loop(void)
{
    pid_t *kidpids = NULL;
    int status;
    int procs = 0;
    int i;

    openlog(prog, LOG_PID, LOG_DAEMON);

    if (setpgid(0, 0)) {
        syslog(LOG_ERR, "fatal: error detaching from parent process group: %s",
               strerror(errno));
        exit(1);
    }
    kidpids = app_malloc(multi * sizeof(*kidpids), "child PID array");
    for (i = 0; i < multi; ++i)
        kidpids[i] = 0;

    signal(SIGINT, noteterm);
    signal(SIGTERM, noteterm);

    while (termsig == 0) {
        pid_t fpid;

        /*
         * Wait for a child to replace when we're at the limit.
         * Slow down if a child exited abnormally or waitpid() < 0
         */
        while (termsig == 0 && procs >= multi) {
            if ((fpid = waitpid(-1, &status, 0)) > 0) {
                for (i = 0; i < procs; ++i) {
                    if (kidpids[i] == fpid) {
                        kidpids[i] = 0;
                        --procs;
                        break;
                    }
                }
                if (i >= multi) {
                    syslog(LOG_ERR, "fatal: internal error: "
                           "no matching child slot for pid: %ld",
                           (long) fpid);
                    killall(1, kidpids);
                }
                if (status != 0) {
                    if (WIFEXITED(status))
                        syslog(LOG_WARNING, "child process: %ld, exit status: %d",
                               (long)fpid, WEXITSTATUS(status));
                    else if (WIFSIGNALED(status))
                        syslog(LOG_WARNING, "child process: %ld, term signal %d%s",
                               (long)fpid, WTERMSIG(status),
#ifdef WCOREDUMP
                               WCOREDUMP(status) ? " (core dumped)" :
#endif
                               "");
                    sleep(1);
                }
                break;
            } else if (errno != EINTR) {
                syslog(LOG_ERR, "fatal: waitpid(): %s", strerror(errno));
                killall(1, kidpids);
            }
        }
        if (termsig)
            break;

        switch(fpid = fork()) {
        case -1:            /* error */
            /* System critically low on memory, pause and try again later */
            sleep(30);
            break;
        case 0:             /* child */
            OPENSSL_free(kidpids);
            signal(SIGINT, SIG_DFL);
            signal(SIGTERM, SIG_DFL);
            if (termsig)
                _exit(0);
            if (RAND_poll() <= 0) {
                syslog(LOG_ERR, "fatal: RAND_poll() failed");
                _exit(1);
            }
            return;
        default:            /* parent */
            for (i = 0; i < multi; ++i) {
                if (kidpids[i] == 0) {
                    kidpids[i] = fpid;
                    procs++;
                    break;
                }
            }
            if (i >= multi) {
                syslog(LOG_ERR, "fatal: internal error: no free child slots");
                killall(1, kidpids);
            }
            break;
        }
    }

    /* The loop above can only break on termsig */
    syslog(LOG_INFO, "terminating on signal: %d", termsig);
    killall(0, kidpids);
}