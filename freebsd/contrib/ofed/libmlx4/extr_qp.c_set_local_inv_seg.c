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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx4_wqe_local_inval_seg {scalar_t__* reserved3; scalar_t__ reserved2; scalar_t__ reserved1; int /*<<< orphan*/  mem_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_local_inv_seg(struct mlx4_wqe_local_inval_seg *iseg,
		uint32_t rkey)
{
	iseg->mem_key	= htobe32(rkey);

	iseg->reserved1    = 0;
	iseg->reserved2    = 0;
	iseg->reserved3[0] = 0;
	iseg->reserved3[1] = 0;
}