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
struct wpa_ctrl {int dummy; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hostapd_cli_action_process ; 
 int /*<<< orphan*/  hostapd_cli_quit ; 
 int /*<<< orphan*/  hostapd_cli_recv_pending (struct wpa_ctrl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  ping_interval ; 
 int /*<<< orphan*/  printf (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int wpa_ctrl_get_fd (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_request (struct wpa_ctrl*,char*,int,char*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_cli_action(struct wpa_ctrl *ctrl)
{
	fd_set rfds;
	int fd, res;
	struct timeval tv;
	char buf[256];
	size_t len;

	fd = wpa_ctrl_get_fd(ctrl);

	while (!hostapd_cli_quit) {
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		tv.tv_sec = ping_interval;
		tv.tv_usec = 0;
		res = select(fd + 1, &rfds, NULL, NULL, &tv);
		if (res < 0 && errno != EINTR) {
			perror("select");
			break;
		}

		if (FD_ISSET(fd, &rfds))
			hostapd_cli_recv_pending(ctrl, 0, 1);
		else {
			len = sizeof(buf) - 1;
			if (wpa_ctrl_request(ctrl, "PING", 4, buf, &len,
					     hostapd_cli_action_process) < 0 ||
			    len < 4 || os_memcmp(buf, "PONG", 4) != 0) {
				printf("hostapd did not reply to PING "
				       "command - exiting\n");
				break;
			}
		}
	}
}