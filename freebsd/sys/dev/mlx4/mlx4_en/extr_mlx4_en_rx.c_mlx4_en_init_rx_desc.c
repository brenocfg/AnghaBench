#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_rx_ring {scalar_t__ buf; } ;
struct mlx4_en_rx_desc {TYPE_3__* data; } ;
struct mlx4_en_priv {TYPE_2__* mdev; scalar_t__ rx_mb_size; } ;
struct TYPE_6__ {scalar_t__ addr; void* lkey; void* byte_count; } ;
struct TYPE_4__ {scalar_t__ key; } ;
struct TYPE_5__ {TYPE_1__ mr; } ;

/* Variables and functions */
 int MLX4_EN_MAX_RX_SEGS ; 
 scalar_t__ MLX4_EN_MEMTYPE_PAD ; 
 scalar_t__ MLX4_NET_IP_ALIGN ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void mlx4_en_init_rx_desc(struct mlx4_en_priv *priv,
				 struct mlx4_en_rx_ring *ring,
				 int index)
{
	struct mlx4_en_rx_desc *rx_desc =
	    ((struct mlx4_en_rx_desc *)ring->buf) + index;
	int i;

	/* Set size and memtype fields */
	rx_desc->data[0].byte_count = cpu_to_be32(priv->rx_mb_size - MLX4_NET_IP_ALIGN);
	rx_desc->data[0].lkey = cpu_to_be32(priv->mdev->mr.key);

	/*
	 * If the number of used fragments does not fill up the ring
	 * stride, remaining (unused) fragments must be padded with
	 * null address/size and a special memory key:
	 */
	for (i = 1; i < MLX4_EN_MAX_RX_SEGS; i++) {
		rx_desc->data[i].byte_count = 0;
		rx_desc->data[i].lkey = cpu_to_be32(MLX4_EN_MEMTYPE_PAD);
		rx_desc->data[i].addr = 0;
	}
}