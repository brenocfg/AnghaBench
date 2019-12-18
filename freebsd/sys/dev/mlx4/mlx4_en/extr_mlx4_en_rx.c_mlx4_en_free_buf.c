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
struct mlx4_en_rx_ring {int /*<<< orphan*/  dma_tag; } ;
struct mlx4_en_rx_mbuf {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  dma_map; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx4_en_free_buf(struct mlx4_en_rx_ring *ring, struct mlx4_en_rx_mbuf *mb_list)
{
	bus_dmamap_t map = mb_list->dma_map;
	bus_dmamap_sync(ring->dma_tag, map, BUS_DMASYNC_POSTREAD);
	bus_dmamap_unload(ring->dma_tag, map);
	m_freem(mb_list->mbuf);
	mb_list->mbuf = NULL;	/* safety clearing */
}