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
struct timeval {int tv_sec; } ;
struct cf_conn {void* strm_stat; scalar_t__ nonblock; } ;
struct TYPE_2__ {int /*<<< orphan*/  xp_fd; scalar_t__ xp_p1; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 void* XPRT_DIED ; 
 int _write (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
write_vc(void *xprtp, void *buf, int len)
{
	SVCXPRT *xprt;
	int i, cnt;
	struct cf_conn *cd;
	struct timeval tv0, tv1;

	xprt = (SVCXPRT *)xprtp;
	assert(xprt != NULL);

	cd = (struct cf_conn *)xprt->xp_p1;

	if (cd->nonblock)
		gettimeofday(&tv0, NULL);
	
	for (cnt = len; cnt > 0; cnt -= i, buf = (char *)buf + i) {
		i = _write(xprt->xp_fd, buf, (size_t)cnt);
		if (i  < 0) {
			if (errno != EAGAIN || !cd->nonblock) {
				cd->strm_stat = XPRT_DIED;
				return (-1);
			}
			if (cd->nonblock) {
				/*
				 * For non-blocking connections, do not
				 * take more than 2 seconds writing the
				 * data out.
				 *
				 * XXX 2 is an arbitrary amount.
				 */
				gettimeofday(&tv1, NULL);
				if (tv1.tv_sec - tv0.tv_sec >= 2) {
					cd->strm_stat = XPRT_DIED;
					return (-1);
				}
			}
			i = 0;
		}
	}

	return (len);
}