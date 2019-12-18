#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pollfd {scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int nfds_t ;
struct TYPE_2__ {int (* poll ) (struct pollfd*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_getd (int /*<<< orphan*/ ) ; 
 scalar_t__ fd_gett (int /*<<< orphan*/ ) ; 
 scalar_t__ fd_rsocket ; 
 struct pollfd* fds_alloc (int) ; 
 int /*<<< orphan*/  init_preload () ; 
 TYPE_1__ real ; 
 int rpoll (struct pollfd*,int,int) ; 
 int stub1 (struct pollfd*,int,int) ; 

int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
	struct pollfd *rfds;
	int i, ret;

	init_preload();
	for (i = 0; i < nfds; i++) {
		if (fd_gett(fds[i].fd) == fd_rsocket)
			goto use_rpoll;
	}

	return real.poll(fds, nfds, timeout);

use_rpoll:
	rfds = fds_alloc(nfds);
	if (!rfds)
		return ERR(ENOMEM);

	for (i = 0; i < nfds; i++) {
		rfds[i].fd = fd_getd(fds[i].fd);
		rfds[i].events = fds[i].events;
		rfds[i].revents = 0;
	}

	ret = rpoll(rfds, nfds, timeout);

	for (i = 0; i < nfds; i++)
		fds[i].revents = rfds[i].revents;

	return ret;
}