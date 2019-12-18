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
struct timeval {int dummy; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct pollfd*) ; 
 int rpoll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_convert_timeout (struct timeval*) ; 
 int rs_poll_to_select (int,struct pollfd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pollfd* rs_select_to_poll (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rselect(int nfds, fd_set *readfds, fd_set *writefds,
	    fd_set *exceptfds, struct timeval *timeout)
{
	struct pollfd *fds;
	int ret;

	fds = rs_select_to_poll(&nfds, readfds, writefds, exceptfds);
	if (!fds)
		return ERR(ENOMEM);

	ret = rpoll(fds, nfds, rs_convert_timeout(timeout));

	if (readfds)
		FD_ZERO(readfds);
	if (writefds)
		FD_ZERO(writefds);
	if (exceptfds)
		FD_ZERO(exceptfds);

	if (ret > 0)
		ret = rs_poll_to_select(nfds, fds, readfds, writefds, exceptfds);

	free(fds);
	return ret;
}