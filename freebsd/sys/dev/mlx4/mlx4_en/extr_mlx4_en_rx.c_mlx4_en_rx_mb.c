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
struct mlx4_en_rx_ring {int /*<<< orphan*/  dma_tag; } ;
struct mlx4_en_rx_mbuf {struct mbuf* mbuf; int /*<<< orphan*/  dma_map; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct mlx4_en_priv {int dummy; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int MHLEN ; 
 int MLX4_NET_IP_ALIGN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caddr_t ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_en_alloc_buf (struct mlx4_en_rx_ring*,struct mlx4_en_rx_desc*,struct mlx4_en_rx_mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct mbuf *
mlx4_en_rx_mb(struct mlx4_en_priv *priv, struct mlx4_en_rx_ring *ring,
    struct mlx4_en_rx_desc *rx_desc, struct mlx4_en_rx_mbuf *mb_list,
    int length)
{
#if (MLX4_EN_MAX_RX_SEGS != 1)
	struct mbuf *mb_head;
#endif
	struct mbuf *mb;

	/* optimise reception of small packets */
	if (length <= (MHLEN - MLX4_NET_IP_ALIGN) &&
	    (mb = m_gethdr(M_NOWAIT, MT_DATA)) != NULL) {

		/* set packet length */
		mb->m_pkthdr.len = mb->m_len = length;

		/* make sure IP header gets aligned */
		mb->m_data += MLX4_NET_IP_ALIGN;

		bus_dmamap_sync(ring->dma_tag, mb_list->dma_map,
		    BUS_DMASYNC_POSTREAD);

		bcopy(mtod(mb_list->mbuf, caddr_t), mtod(mb, caddr_t), length);

		return (mb);
	}

	/* get mbuf */
	mb = mb_list->mbuf;

	/* collect used fragment while atomically replacing it */
	if (mlx4_en_alloc_buf(ring, rx_desc, mb_list))
		return (NULL);

	/* range check hardware computed value */
	if (unlikely(length > mb->m_pkthdr.len))
		length = mb->m_pkthdr.len;

#if (MLX4_EN_MAX_RX_SEGS == 1)
	/* update total packet length in packet header */
	mb->m_len = mb->m_pkthdr.len = length;
#else
	mb->m_pkthdr.len = length;
	for (mb_head = mb; mb != NULL; mb = mb->m_next) {
		if (mb->m_len > length)
			mb->m_len = length;
		length -= mb->m_len;
		if (likely(length == 0)) {
			if (likely(mb->m_next != NULL)) {
				/* trim off empty mbufs */
				m_freem(mb->m_next);
				mb->m_next = NULL;
			}
			break;
		}
	}
	/* rewind to first mbuf in chain */
	mb = mb_head;
#endif
	return (mb);
}