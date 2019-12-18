#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  _pid; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (TYPE_1__*) ; 

__attribute__((used)) static void
close_pipe(FILE *pipefd)
{
	if (pipefd == NULL)
		return;
#if OS2
	/*
	 * The pclose function of OS/2 emx sometimes fails.
	 * Send SIGINT to the piped process before closing it.
	 */
	kill(pipefd->_pid, SIGINT);
#endif
	pclose(pipefd);
}