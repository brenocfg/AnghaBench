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
struct mlx4_en_rx_ring {struct mlx4_en_rx_mbuf* mbuf; scalar_t__ buf; } ;
struct mlx4_en_rx_mbuf {int /*<<< orphan*/ * mbuf; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_alloc_failed; } ;
struct mlx4_en_priv {TYPE_1__ port_stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ mlx4_en_alloc_buf (struct mlx4_en_rx_ring*,struct mlx4_en_rx_desc*,struct mlx4_en_rx_mbuf*) ; 

__attribute__((used)) static int
mlx4_en_prepare_rx_desc(struct mlx4_en_priv *priv,
    struct mlx4_en_rx_ring *ring, int index)
{
	struct mlx4_en_rx_desc *rx_desc =
	    ((struct mlx4_en_rx_desc *)ring->buf) + index;
	struct mlx4_en_rx_mbuf *mb_list = ring->mbuf + index;

	mb_list->mbuf = NULL;

	if (mlx4_en_alloc_buf(ring, rx_desc, mb_list)) {
		priv->port_stats.rx_alloc_failed++;
		return (-ENOMEM);
	}
	return (0);
}