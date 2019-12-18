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
struct mlx4_wqe_data_seg {void* byte_count; int /*<<< orphan*/  addr; void* lkey; } ;
struct ibv_sge {int lkey; int length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 void* htobe32 (int) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 

__attribute__((used)) static void set_data_seg(struct mlx4_wqe_data_seg *dseg, struct ibv_sge *sg)
{
	dseg->lkey       = htobe32(sg->lkey);
	dseg->addr       = htobe64(sg->addr);

	/*
	 * Need a barrier here before writing the byte_count field to
	 * make sure that all the data is visible before the
	 * byte_count field is set.  Otherwise, if the segment begins
	 * a new cacheline, the HCA prefetcher could grab the 64-byte
	 * chunk and get a valid (!= * 0xffffffff) byte count but
	 * stale data, and end up sending the wrong data.
	 */
	udma_to_device_barrier();

	if (likely(sg->length))
		dseg->byte_count = htobe32(sg->length);
	else
		dseg->byte_count = htobe32(0x80000000);
}