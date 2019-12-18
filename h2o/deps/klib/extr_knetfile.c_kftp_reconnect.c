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
struct TYPE_4__ {int ctrl_fd; int fd; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int kftp_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  netclose (int) ; 

int kftp_reconnect(knetFile *ftp)
{
	if (ftp->ctrl_fd != -1) {
		netclose(ftp->ctrl_fd);
		ftp->ctrl_fd = -1;
	}
	netclose(ftp->fd);
	ftp->fd = -1;
	return kftp_connect(ftp);
}