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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIGURG ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int errno ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transflag ; 

__attribute__((used)) static void
maskurg(int flag)
{
	int oerrno;
	sigset_t sset;

	if (!transflag) {
		syslog(LOG_ERR, "Internal: maskurg() while no transfer");
		return;
	}
	oerrno = errno;
	sigemptyset(&sset);
	sigaddset(&sset, SIGURG);
	sigprocmask(flag ? SIG_BLOCK : SIG_UNBLOCK, &sset, NULL);
	errno = oerrno;
}