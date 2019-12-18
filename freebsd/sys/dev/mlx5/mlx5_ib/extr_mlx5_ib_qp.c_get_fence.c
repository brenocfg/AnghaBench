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
typedef  int u8 ;
struct ib_send_wr {scalar_t__ opcode; int send_flags; } ;

/* Variables and functions */
 int IB_SEND_FENCE ; 
 scalar_t__ IB_WR_LOCAL_INV ; 
 int MLX5_FENCE_MODE_FENCE ; 
 int MLX5_FENCE_MODE_SMALL_AND_FENCE ; 
 int MLX5_FENCE_MODE_STRONG_ORDERING ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u8 get_fence(u8 fence, struct ib_send_wr *wr)
{
	if (unlikely(wr->opcode == IB_WR_LOCAL_INV &&
		     wr->send_flags & IB_SEND_FENCE))
		return MLX5_FENCE_MODE_STRONG_ORDERING;

	if (unlikely(fence)) {
		if (wr->send_flags & IB_SEND_FENCE)
			return MLX5_FENCE_MODE_SMALL_AND_FENCE;
		else
			return fence;
	} else if (unlikely(wr->send_flags & IB_SEND_FENCE)) {
		return MLX5_FENCE_MODE_FENCE;
	}

	return 0;
}