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
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TIOCOUTQ ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int wpas_ctrl_iface_throttle(int sock)
{
#ifdef __linux__
	socklen_t optlen;
	int sndbuf, outq;

	optlen = sizeof(sndbuf);
	sndbuf = 0;
	if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen) < 0 ||
	    ioctl(sock, TIOCOUTQ, &outq) < 0 ||
	    sndbuf <= 0 || outq < 0)
		return 0;
	return outq > sndbuf / 2;
#else /* __linux__ */
	return 0;
#endif /* __linux__ */
}