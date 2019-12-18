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
typedef  scalar_t__ uint32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ polling_time ; 
 struct pollfd* rs_fds_alloc (int /*<<< orphan*/ ) ; 
 int rs_poll_arm (struct pollfd*,struct pollfd*,int /*<<< orphan*/ ) ; 
 int rs_poll_check (struct pollfd*,int /*<<< orphan*/ ) ; 
 int rs_poll_events (struct pollfd*,struct pollfd*,int /*<<< orphan*/ ) ; 

int rpoll(struct pollfd *fds, nfds_t nfds, int timeout)
{
	struct timeval s, e;
	struct pollfd *rfds;
	uint32_t poll_time = 0;
	int ret;

	do {
		ret = rs_poll_check(fds, nfds);
		if (ret || !timeout)
			return ret;

		if (!poll_time)
			gettimeofday(&s, NULL);

		gettimeofday(&e, NULL);
		poll_time = (e.tv_sec - s.tv_sec) * 1000000 +
			    (e.tv_usec - s.tv_usec) + 1;
	} while (poll_time <= polling_time);

	rfds = rs_fds_alloc(nfds);
	if (!rfds)
		return ERR(ENOMEM);

	do {
		ret = rs_poll_arm(rfds, fds, nfds);
		if (ret)
			break;

		ret = poll(rfds, nfds, timeout);
		if (ret <= 0)
			break;

		ret = rs_poll_events(rfds, fds, nfds);
	} while (!ret);

	return ret;
}