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
 struct pollfd* fds_alloc (int) ; 
 int rpoll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int rpoll_to_select (struct pollfd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs_convert_timeout (struct timeval*) ; 
 int /*<<< orphan*/  select_to_rpoll (struct pollfd*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int select(int nfds, fd_set *readfds, fd_set *writefds,
	   fd_set *exceptfds, struct timeval *timeout)
{
	struct pollfd *fds;
	int ret;

	fds = fds_alloc(nfds);
	if (!fds)
		return ERR(ENOMEM);

	select_to_rpoll(fds, &nfds, readfds, writefds, exceptfds);
	ret = rpoll(fds, nfds, rs_convert_timeout(timeout));

	if (readfds)
		FD_ZERO(readfds);
	if (writefds)
		FD_ZERO(writefds);
	if (exceptfds)
		FD_ZERO(exceptfds);

	if (ret > 0)
		ret = rpoll_to_select(fds, nfds, readfds, writefds, exceptfds);

	return ret;
}