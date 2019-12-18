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
typedef  int /*<<< orphan*/  uint8_t ;
struct net_backend {int dummy; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  dummybuf ;

/* Variables and functions */
 int /*<<< orphan*/  netbe_recv (struct net_backend*,struct iovec*,int) ; 

ssize_t
netbe_rx_discard(struct net_backend *be)
{
	/*
	 * MP note: the dummybuf is only used to discard frames,
	 * so there is no need for it to be per-vtnet or locked.
	 * We only make it large enough for TSO-sized segment.
	 */
	static uint8_t dummybuf[65536 + 64];
	struct iovec iov;

	iov.iov_base = dummybuf;
	iov.iov_len = sizeof(dummybuf);

	return netbe_recv(be, &iov, 1);
}