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
 char* NOSTR ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  daemon_uid () ; 
 int /*<<< orphan*/  disconnect (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipout_pid ; 
 int /*<<< orphan*/  unexcl () ; 
 int /*<<< orphan*/  unraw () ; 
 int /*<<< orphan*/  uu_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uucplock ; 

void
tipabort(char *msg)
{

	signal(SIGTERM, SIG_IGN);
	kill(tipout_pid, SIGTERM);
	disconnect(msg);
	if (msg != NOSTR)
		printf("\r\n%s", msg);
	printf("\r\n[EOT]\r\n");
	daemon_uid();
	(void)uu_unlock(uucplock);
	unraw();
	unexcl();
	exit(0);
}