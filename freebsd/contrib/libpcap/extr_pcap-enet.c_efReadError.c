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
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
efReadError(int fid, char *msg)
{
	if (errno == EINVAL) {	/* read MAXINT bytes already! */
		if (lseek(fid, 0, 0) < 0) {
			perror("tcpdump: efReadError/lseek");
			exit(-1);
		}
		else
			return;
	}
	else {
		(void) fprintf(stderr, "tcpdump: ");
		perror(msg);
		exit(-1);
	}
}