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
struct mlx4_en_tx_ring {int size; int prod; int cons; } ;

/* Variables and functions */
 int HEADROOM ; 
 int MLX4_EN_TX_WQE_MAX_WQEBBS ; 

__attribute__((used)) static bool
mlx4_en_tx_ring_is_full(struct mlx4_en_tx_ring *ring)
{
	int wqs;
	wqs = ring->size - (ring->prod - ring->cons);
	return (wqs < (HEADROOM + (2 * MLX4_EN_TX_WQE_MAX_WQEBBS)));
}