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
typedef  int ssize_t ;
struct TYPE_2__ {int** sync_fd; scalar_t__ server_flag; } ;

/* Variables and functions */
 size_t SYNC_CLIENT ; 
 size_t SYNC_SEND ; 
 size_t SYNC_SERVER ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_dbgmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsgx (char*,int) ; 
 int write (int,char*,int) ; 

int
uc_sync_send(void)
{
	ssize_t ssize;
	int fd;

	uc_dbgmsg("sync: send");

	fd = uc_cfg.sync_fd[uc_cfg.server_flag ? SYNC_CLIENT : SYNC_SERVER][SYNC_SEND];

	ssize = write(fd, "", 1);
	if (ssize < 0) {
		uc_logmsg("uc_sync_send: write");
		return (-1);
	}
	if (ssize < 1) {
		uc_logmsgx("uc_sync_send: sent %zd of 1 byte", ssize);
		return (-1);
	}

	return (0);
}