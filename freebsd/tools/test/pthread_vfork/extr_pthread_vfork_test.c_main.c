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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  reapchildren ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int NUM_THREADS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errc (int,int,char*) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause () ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfork_test ; 

int
main(void)
{
	pthread_t threads[NUM_THREADS];
	struct sigaction reapchildren;
	sigset_t sigchld_mask;
	int rc, t;

	memset(&reapchildren, 0, sizeof(reapchildren));
	reapchildren.sa_handler = sighandler;
	if (sigaction(SIGCHLD, &reapchildren, NULL) == -1)
		err(1, "Could not sigaction(SIGCHLD)");

	sigemptyset(&sigchld_mask);
	sigaddset(&sigchld_mask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &sigchld_mask, NULL) == -1)
		err(1, "sigprocmask");

	for (t = 0; t < NUM_THREADS; t++) {
		rc = pthread_create(&threads[t], NULL, vfork_test, &t);
		if (rc)
			errc(1, rc, "pthread_create");
	}
	pause();
	return (0);
}