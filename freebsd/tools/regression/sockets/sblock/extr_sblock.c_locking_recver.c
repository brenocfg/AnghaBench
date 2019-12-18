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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  interrupted ; 
 scalar_t__ recv (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sleep (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
locking_recver(int fd)
{
	ssize_t len;
	char ch;

	if (sleep(1) != 0)
		err(-1, "FAIL: locking_recver: sleep");
	len = recv(fd, &ch, sizeof(ch), 0);
	if (len < 0 && errno != EINTR)
		err(-1, "FAIL: locking_recver: recv");
	if (len < 0 && errno == EINTR) {
		fprintf(stderr, "PASS\n");
		exit(0);
	}
	if (len == 0)
		errx(-1, "FAIL: locking_recver: recv: eof");
	if (!interrupted)
		errx(-1, "FAIL: locking_recver: not interrupted");
}