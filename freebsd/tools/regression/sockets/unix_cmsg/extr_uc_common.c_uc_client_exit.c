#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** sync_fd; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 size_t SYNC_CLIENT ; 
 size_t SYNC_RECV ; 
 size_t SYNC_SEND ; 
 size_t SYNC_SERVER ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_dbgmsg (char*,int) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 

void
uc_client_exit(int rv)
{
	if (close(uc_cfg.sync_fd[SYNC_SERVER][SYNC_SEND]) < 0 ||
	    close(uc_cfg.sync_fd[SYNC_CLIENT][SYNC_RECV]) < 0) {
		uc_logmsg("client_exit: close");
		rv = -1;
	}
	rv = rv == 0 ? EXIT_SUCCESS : -rv;
	uc_dbgmsg("exit: code %d", rv);
	_exit(rv);
}