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
struct virtio_net_rxhdr {int vrh_bufs; } ;
struct net_backend {unsigned int fe_vnet_hdr_len; unsigned int be_vnet_hdr_len; int (* recv ) (struct net_backend*,struct iovec*,int) ;} ;
struct iovec {struct virtio_net_rxhdr* iov_base; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int VNET_HDR_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 struct iovec* iov_trim (struct iovec*,int*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct virtio_net_rxhdr*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct net_backend*,struct iovec*,int) ; 

ssize_t
netbe_recv(struct net_backend *be, struct iovec *iov, int iovcnt)
{
	/* Length of prepended virtio-net header. */
	unsigned int hlen = be->fe_vnet_hdr_len;
	int ret;

	assert(be != NULL);

	if (hlen && hlen != be->be_vnet_hdr_len) {
		/*
		 * The frontend uses a virtio-net header, but the backend
		 * does not. We need to prepend a zeroed header.
		 */
		struct virtio_net_rxhdr *vh;

		assert(be->be_vnet_hdr_len == 0);

		/*
		 * Get a pointer to the rx header, and use the
		 * data immediately following it for the packet buffer.
		 */
		vh = iov[0].iov_base;
		iov = iov_trim(iov, &iovcnt, hlen);

		/*
		 * The only valid field in the rx packet header is the
		 * number of buffers if merged rx bufs were negotiated.
		 */
		memset(vh, 0, hlen);
		if (hlen == VNET_HDR_LEN) {
			vh->vrh_bufs = 1;
		}
	}

	ret = be->recv(be, iov, iovcnt);
	if (ret > 0) {
		ret += hlen;
	}

	return (ret);
}