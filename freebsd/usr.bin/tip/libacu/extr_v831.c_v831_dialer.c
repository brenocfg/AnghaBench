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
typedef  int pid_t ;

/* Variables and functions */
 void* AC ; 
 char* DV ; 
 int EBUSY ; 
 int EIO ; 
 void* FD ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  alarmtr ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int child ; 
 int /*<<< orphan*/  close (void*) ; 
 char dialit (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 void* open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int wait (int*) ; 

int
v831_dialer(char *num, char *acu)
{
        int status;
        int timelim;
	pid_t pid;

        if (boolean(value(VERBOSE)))
                printf("\nstarting call...");
#ifdef DEBUG
        printf ("(acu=%s)\n", acu);
#endif
        if ((AC = open(acu, O_RDWR)) < 0) {
                if (errno == EBUSY)
                        printf("line busy...");
                else
                        printf("acu open error...");
                return (0);
        }
        if (setjmp(jmpbuf)) {
                kill(child, SIGKILL);
                close(AC);
                return (0);
        }
        signal(SIGALRM, alarmtr);
        timelim = 5 * strlen(num);
        alarm(timelim < 30 ? 30 : timelim);
        if ((child = fork()) == 0) {
                /*
                 * ignore this stuff for aborts
                 */
                signal(SIGALRM, SIG_IGN);
		signal(SIGINT, SIG_IGN);
                signal(SIGQUIT, SIG_IGN);
                sleep(2);
                exit(dialit(num, acu) != 'A');
        }
        /*
         * open line - will return on carrier
         */
        if ((FD = open(DV, O_RDWR)) < 0) {
#ifdef DEBUG
                printf("(after open, errno=%d)\n", errno);
#endif
                if (errno == EIO)
                        printf("lost carrier...");
                else
                        printf("dialup line open failed...");
                alarm(0);
                kill(child, SIGKILL);
                close(AC);
                return (0);
        }
        alarm(0);
        signal(SIGALRM, SIG_DFL);
        while ((pid = wait(&status)) != child && pid != -1)
                ;
        if (status) {
                close(AC);
                return (0);
        }
        return (1);
}