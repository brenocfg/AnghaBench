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
struct mlx4_wqe_raddr_seg {int dummy; } ;
struct mlx4_wqe_inline_seg {int dummy; } ;
struct mlx4_wqe_datagram_seg {int dummy; } ;
struct mlx4_wqe_ctrl_seg {int dummy; } ;
typedef  enum ibv_qp_type { ____Placeholder_ibv_qp_type } ibv_qp_type ;

/* Variables and functions */
 int IBV_QPT_UD ; 
 int MLX4_INLINE_ALIGN ; 

__attribute__((used)) static int num_inline_segs(int data, enum ibv_qp_type type)
{
	/*
	 * Inline data segments are not allowed to cross 64 byte
	 * boundaries.  For UD QPs, the data segments always start
	 * aligned to 64 bytes (16 byte control segment + 48 byte
	 * datagram segment); for other QPs, there will be a 16 byte
	 * control segment and possibly a 16 byte remote address
	 * segment, so in the worst case there will be only 32 bytes
	 * available for the first data segment.
	 */
	if (type == IBV_QPT_UD)
		data += (sizeof (struct mlx4_wqe_ctrl_seg) +
			 sizeof (struct mlx4_wqe_datagram_seg)) %
			MLX4_INLINE_ALIGN;
	else
		data += (sizeof (struct mlx4_wqe_ctrl_seg) +
			 sizeof (struct mlx4_wqe_raddr_seg)) %
			MLX4_INLINE_ALIGN;

	return (data + MLX4_INLINE_ALIGN - sizeof (struct mlx4_wqe_inline_seg) - 1) /
		(MLX4_INLINE_ALIGN - sizeof (struct mlx4_wqe_inline_seg));
}