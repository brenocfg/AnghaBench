#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ctrl_fd; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  kftp_get_response (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_send_cmd (TYPE_1__*,char*,int) ; 
 int socket_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kftp_connect(knetFile *ftp)
{
	ftp->ctrl_fd = socket_connect(ftp->host, ftp->port);
	if (ftp->ctrl_fd == -1) return -1;
	kftp_get_response(ftp);
	kftp_send_cmd(ftp, "USER anonymous\r\n", 1);
	kftp_send_cmd(ftp, "PASS kftp@\r\n", 1);
	kftp_send_cmd(ftp, "TYPE I\r\n", 1);
	return 0;
}