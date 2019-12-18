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
 int /*<<< orphan*/  AFILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RENDEZVOUS ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
openfiles2(size_t n)
{
	size_t i;
	int r;

	errno = 0;
	for (i = 0; i < n; i++) {
		r = open(AFILE, O_RDONLY);
		if (r < 0) {
			fprintf(stderr, "open: %s\n", strerror(errno));
			_exit(1);
		}
	}
	kill(getppid(), SIGUSR1);

	for (;;) {
		if (access(RENDEZVOUS, R_OK) != 0)
			break;
		usleep(1000);
	}
	_exit(0);
}