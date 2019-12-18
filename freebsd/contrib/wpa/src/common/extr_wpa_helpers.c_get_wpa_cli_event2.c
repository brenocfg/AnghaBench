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
typedef  scalar_t__ time_t ;
struct wpa_ctrl {int dummy; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int default_timeout ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 char* strchr (char*,char) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int wpa_ctrl_get_fd (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_recv (struct wpa_ctrl*,char*,size_t*) ; 

int get_wpa_cli_event2(struct wpa_ctrl *mon,
		       const char *event, const char *event2,
		       char *buf, size_t buf_size)
{
	int fd, ret;
	fd_set rfd;
	char *pos;
	struct timeval tv;
	time_t start, now;

	printf("Waiting for wpa_cli event %s\n", event);
	fd = wpa_ctrl_get_fd(mon);
	if (fd < 0)
		return -1;

	time(&start);
	while (1) {
		size_t len;

		FD_ZERO(&rfd);
		FD_SET(fd, &rfd);
		tv.tv_sec = default_timeout;
		tv.tv_usec = 0;
		ret = select(fd + 1, &rfd, NULL, NULL, &tv);
		if (ret == 0) {
			printf("Timeout on waiting for event %s\n", event);
			return -1;
		}
		if (ret < 0) {
			printf("select: %s\n", strerror(errno));
			return -1;
		}
		len = buf_size;
		if (wpa_ctrl_recv(mon, buf, &len) < 0) {
			printf("Failure while waiting for event %s\n", event);
			return -1;
		}
		if (len == buf_size)
			len--;
		buf[len] = '\0';

		pos = strchr(buf, '>');
		if (pos &&
		    (strncmp(pos + 1, event, strlen(event)) == 0 ||
		     (event2 &&
		      strncmp(pos + 1, event2, strlen(event2)) == 0)))
			return 0; /* Event found */

		time(&now);
		if ((int) (now - start) > default_timeout) {
			printf("Timeout on waiting for event %s\n", event);
			return -1;
		}
	}
}