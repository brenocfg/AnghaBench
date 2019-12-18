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
struct net_backend {scalar_t__ be_vnet_hdr_len; scalar_t__ fe_vnet_hdr_len; int /*<<< orphan*/  (* send ) (struct net_backend*,struct iovec*,int) ;} ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct iovec* iov_trim (struct iovec*,int*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_backend*,struct iovec*,int) ; 

ssize_t
netbe_send(struct net_backend *be, struct iovec *iov, int iovcnt)
{

	assert(be != NULL);
	if (be->be_vnet_hdr_len != be->fe_vnet_hdr_len) {
		/*
		 * The frontend uses a virtio-net header, but the backend
		 * does not. We ignore it (as it must be all zeroes) and
		 * strip it.
		 */
		assert(be->be_vnet_hdr_len == 0);
		iov = iov_trim(iov, &iovcnt, be->fe_vnet_hdr_len);
	}

	return (be->send(be, iov, iovcnt));
}