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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sndbuf ;

/* Variables and functions */
 int MSG_EXCESSIVE ; 
 int MSG_MSGDUMP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TIOCOUTQ ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int,char*,char const*,int,int,int,int) ; 

__attribute__((used)) static void wpas_ctrl_sock_debug(const char *title, int sock, const char *buf,
				 size_t len)
{
#ifdef __linux__
	socklen_t optlen;
	int sndbuf, outq;
	int level = MSG_MSGDUMP;

	if (len >= 5 && os_strncmp(buf, "PONG\n", 5) == 0)
		level = MSG_EXCESSIVE;

	optlen = sizeof(sndbuf);
	sndbuf = 0;
	if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen) < 0)
		sndbuf = -1;

	if (ioctl(sock, TIOCOUTQ, &outq) < 0)
		outq = -1;

	wpa_printf(level,
		   "CTRL-DEBUG: %s: sock=%d sndbuf=%d outq=%d send_len=%d",
		   title, sock, sndbuf, outq, (int) len);
#endif /* __linux__ */
}