#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tv ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_len; } ;
struct TYPE_4__ {scalar_t__ sock_type; int serv_sock_fd; TYPE_1__ serv_addr_sun; scalar_t__ server_flag; int /*<<< orphan*/  sock_type_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LISTENQ ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  TIMEOUT ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ uc_cfg ; 
 int /*<<< orphan*/  uc_logmsg (char*,...) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

int
uc_socket_create(void)
{
	struct timeval tv;
	int fd;

	fd = socket(PF_LOCAL, uc_cfg.sock_type, 0);
	if (fd < 0) {
		uc_logmsg("socket_create: socket(PF_LOCAL, %s, 0)", uc_cfg.sock_type_str);
		return (-1);
	}
	if (uc_cfg.server_flag)
		uc_cfg.serv_sock_fd = fd;

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0 ||
	    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0) {
		uc_logmsg("socket_create: setsockopt(SO_RCVTIMEO/SO_SNDTIMEO)");
		goto failed;
	}

	if (uc_cfg.server_flag) {
		if (bind(fd, (struct sockaddr *)&uc_cfg.serv_addr_sun,
		    uc_cfg.serv_addr_sun.sun_len) < 0) {
			uc_logmsg("socket_create: bind(%s)",
			    uc_cfg.serv_addr_sun.sun_path);
			goto failed;
		}
		if (uc_cfg.sock_type == SOCK_STREAM) {
			int val;

			if (listen(fd, LISTENQ) < 0) {
				uc_logmsg("socket_create: listen");
				goto failed;
			}
			val = fcntl(fd, F_GETFL, 0);
			if (val < 0) {
				uc_logmsg("socket_create: fcntl(F_GETFL)");
				goto failed;
			}
			if (fcntl(fd, F_SETFL, val | O_NONBLOCK) < 0) {
				uc_logmsg("socket_create: fcntl(F_SETFL)");
				goto failed;
			}
		}
	}

	return (fd);

failed:
	if (close(fd) < 0)
		uc_logmsg("socket_create: close");
	if (uc_cfg.server_flag)
		if (unlink(uc_cfg.serv_addr_sun.sun_path) < 0)
			uc_logmsg("socket_close: unlink(%s)",
			    uc_cfg.serv_addr_sun.sun_path);
	return (-1);
}