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
typedef  int uint16_t ;
struct vqueue_info {int dummy; } ;
struct virtio_net_rxhdr {int vrh_bufs; } ;
struct virtio_mrg_rxbuf_info {scalar_t__ len; int /*<<< orphan*/  idx; } ;
struct pci_vtnet_softc {int /*<<< orphan*/  rx_merge; int /*<<< orphan*/  vsc_be; struct vqueue_info* vsc_queues; } ;
struct iovec {int iov_len; struct virtio_net_rxhdr* iov_base; } ;

/* Variables and functions */
 int VTNET_MAXSEGS ; 
 scalar_t__ VTNET_MAX_PKT_LEN ; 
 size_t VTNET_RXQ ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ count_iov (struct iovec*,int) ; 
 int netbe_recv (int /*<<< orphan*/ ,struct iovec*,int) ; 
 int /*<<< orphan*/  netbe_rx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_endchains (struct vqueue_info*,int) ; 
 int vq_getchain (struct vqueue_info*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_kick_disable (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_kick_enable (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vq_relchain_prepare (struct vqueue_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vq_relchain_publish (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_retchains (struct vqueue_info*,int) ; 

__attribute__((used)) static void
pci_vtnet_rx(struct pci_vtnet_softc *sc)
{
	struct virtio_mrg_rxbuf_info info[VTNET_MAXSEGS];
	struct iovec iov[VTNET_MAXSEGS + 1];
	struct vqueue_info *vq;
	uint32_t cur_iov_bytes;
	struct iovec *cur_iov;
	uint16_t cur_iov_len;
	uint32_t ulen;
	int n_chains;
	int len;

	vq = &sc->vsc_queues[VTNET_RXQ];
	for (;;) {
		/*
		 * Get a descriptor chain to store the next ingress
		 * packet. In case of mergeable rx buffers, get as
		 * many chains as necessary in order to make room
		 * for a maximum sized LRO packet.
		 */
		cur_iov_bytes = 0;
		cur_iov_len = 0;
		cur_iov = iov;
		n_chains = 0;
		do {
			int n = vq_getchain(vq, &info[n_chains].idx, cur_iov,
			    VTNET_MAXSEGS - cur_iov_len, NULL);

			if (n == 0) {
				/*
				 * No rx buffers. Enable RX kicks and double
				 * check.
				 */
				vq_kick_enable(vq);
				if (!vq_has_descs(vq)) {
					/*
					 * Still no buffers. Return the unused
					 * chains (if any), interrupt if needed
					 * (including for NOTIFY_ON_EMPTY), and
					 * disable the backend until the next
					 * kick.
					 */
					vq_retchains(vq, n_chains);
					vq_endchains(vq, /*used_all_avail=*/1);
					netbe_rx_disable(sc->vsc_be);
					return;
				}

				/* More rx buffers found, so keep going. */
				vq_kick_disable(vq);
				continue;
			}
			assert(n >= 1 && cur_iov_len + n <= VTNET_MAXSEGS);
			cur_iov_len += n;
			if (!sc->rx_merge) {
				n_chains = 1;
				break;
			}
			info[n_chains].len = (uint32_t)count_iov(cur_iov, n);
			cur_iov_bytes += info[n_chains].len;
			cur_iov += n;
			n_chains++;
		} while (cur_iov_bytes < VTNET_MAX_PKT_LEN &&
			    cur_iov_len < VTNET_MAXSEGS);

		len = netbe_recv(sc->vsc_be, iov, cur_iov_len);

		if (len <= 0) {
			/*
			 * No more packets (len == 0), or backend errored
			 * (err < 0). Return unused available buffers
			 * and stop.
			 */
			vq_retchains(vq, n_chains);
			/* Interrupt if needed/appropriate and stop. */
			vq_endchains(vq, /*used_all_avail=*/0);
			return;
		}

		ulen = (uint32_t)len; /* avoid too many casts below */

		/* Publish the used buffers to the guest. */
		if (!sc->rx_merge) {
			vq_relchain(vq, info[0].idx, ulen);
		} else {
			struct virtio_net_rxhdr *hdr = iov[0].iov_base;
			uint32_t iolen;
			int i = 0;

			assert(iov[0].iov_len >= sizeof(*hdr));

			do {
				iolen = info[i].len;
				if (iolen > ulen) {
					iolen = ulen;
				}
				vq_relchain_prepare(vq, info[i].idx, iolen);
				ulen -= iolen;
				i++;
				assert(i <= n_chains);
			} while (ulen > 0);

			hdr->vrh_bufs = i;
			vq_relchain_publish(vq);
			vq_retchains(vq, n_chains - i);
		}
	}

}