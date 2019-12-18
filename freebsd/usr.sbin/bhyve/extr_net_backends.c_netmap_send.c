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
typedef  size_t uint32_t ;
struct netmap_ring {size_t head; size_t tail; int nr_buf_size; size_t cur; TYPE_1__* slot; } ;
struct netmap_priv {struct netmap_ring* tx; } ;
struct net_backend {int /*<<< orphan*/  fd; scalar_t__ opaque; } ;
struct iovec {int iov_len; void* iov_base; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int len; scalar_t__ flags; int /*<<< orphan*/  buf_idx; } ;

/* Variables and functions */
 void* NETMAP_BUF (struct netmap_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIOCTXSYNC ; 
 scalar_t__ NS_MOREFRAG ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  count_iov (struct iovec*,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 size_t nm_ring_next (struct netmap_ring*,size_t) ; 

__attribute__((used)) static ssize_t
netmap_send(struct net_backend *be, struct iovec *iov,
	    int iovcnt)
{
	struct netmap_priv *priv = (struct netmap_priv *)be->opaque;
	struct netmap_ring *ring;
	ssize_t totlen = 0;
	int nm_buf_size;
	int nm_buf_len;
	uint32_t head;
	void *nm_buf;
	int j;

	ring = priv->tx;
	head = ring->head;
	if (head == ring->tail) {
		WPRINTF(("No space, drop %zu bytes\n", count_iov(iov, iovcnt)));
		goto txsync;
	}
	nm_buf = NETMAP_BUF(ring, ring->slot[head].buf_idx);
	nm_buf_size = ring->nr_buf_size;
	nm_buf_len = 0;

	for (j = 0; j < iovcnt; j++) {
		int iov_frag_size = iov[j].iov_len;
		void *iov_frag_buf = iov[j].iov_base;

		totlen += iov_frag_size;

		/*
		 * Split each iovec fragment over more netmap slots, if
		 * necessary.
		 */
		for (;;) {
			int copylen;

			copylen = iov_frag_size < nm_buf_size ? iov_frag_size : nm_buf_size;
			memcpy(nm_buf, iov_frag_buf, copylen);

			iov_frag_buf += copylen;
			iov_frag_size -= copylen;
			nm_buf += copylen;
			nm_buf_size -= copylen;
			nm_buf_len += copylen;

			if (iov_frag_size == 0) {
				break;
			}

			ring->slot[head].len = nm_buf_len;
			ring->slot[head].flags = NS_MOREFRAG;
			head = nm_ring_next(ring, head);
			if (head == ring->tail) {
				/*
				 * We ran out of netmap slots while
				 * splitting the iovec fragments.
				 */
				WPRINTF(("No space, drop %zu bytes\n",
				   count_iov(iov, iovcnt)));
				goto txsync;
			}
			nm_buf = NETMAP_BUF(ring, ring->slot[head].buf_idx);
			nm_buf_size = ring->nr_buf_size;
			nm_buf_len = 0;
		}
	}

	/* Complete the last slot, which must not have NS_MOREFRAG set. */
	ring->slot[head].len = nm_buf_len;
	ring->slot[head].flags = 0;
	head = nm_ring_next(ring, head);

	/* Now update ring->head and ring->cur. */
	ring->head = ring->cur = head;
txsync:
	ioctl(be->fd, NIOCTXSYNC, NULL);

	return (totlen);
}