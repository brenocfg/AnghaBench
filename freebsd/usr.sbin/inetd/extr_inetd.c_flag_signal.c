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
typedef  int /*<<< orphan*/  signo ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * signalpipe ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 size_t write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
flag_signal(int signo)
{
	size_t len;

	len = write(signalpipe[1], &signo, sizeof(signo));
	if (len != sizeof(signo)) {
		syslog(LOG_ERR, "write: %m");
		_exit(EX_OSERR);
	}
}