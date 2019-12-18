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
typedef  int /*<<< orphan*/  bufsiz_wanted ;
typedef  int /*<<< orphan*/  bufsiz_current ;

/* Variables and functions */
 int /*<<< orphan*/  EIPSEC_NO_ERROR ; 
 int /*<<< orphan*/  PF_KEY ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  __ipsec_errcode ; 
 int /*<<< orphan*/  __ipsec_set_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
pfkey_open(void)
{
	int so;
	int bufsiz_current, bufsiz_wanted;
	int ret;
	socklen_t len;

	if ((so = socket(PF_KEY, SOCK_RAW, PF_KEY_V2)) < 0) {
		__ipsec_set_strerror(strerror(errno));
		return -1;
	}

	/*
	 * This is a temporary workaround for KAME PR 154.
	 * Don't really care even if it fails.
	 */
	/* Try to have 128k. If we have more, do not lower it. */
	bufsiz_wanted = 128 * 1024;
	len = sizeof(bufsiz_current);
	ret = getsockopt(so, SOL_SOCKET, SO_SNDBUF,
		&bufsiz_current, &len);
	if ((ret < 0) || (bufsiz_current < bufsiz_wanted))
		(void)setsockopt(so, SOL_SOCKET, SO_SNDBUF,
			&bufsiz_wanted, sizeof(bufsiz_wanted));

	/* Try to have have at least 2MB. If we have more, do not lower it. */
	bufsiz_wanted = 2 * 1024 * 1024;
	len = sizeof(bufsiz_current);
	ret = getsockopt(so, SOL_SOCKET, SO_RCVBUF,
		&bufsiz_current, &len);
	if (ret < 0)
		bufsiz_current = 128 * 1024;

	for (; bufsiz_wanted > bufsiz_current; bufsiz_wanted /= 2) {
		if (setsockopt(so, SOL_SOCKET, SO_RCVBUF,
				&bufsiz_wanted, sizeof(bufsiz_wanted)) == 0)
			break;
	}

	__ipsec_errcode = EIPSEC_NO_ERROR;
	return so;
}