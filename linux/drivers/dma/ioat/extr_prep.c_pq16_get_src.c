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
struct ioat_raw_descriptor {int /*<<< orphan*/ * field; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t* pq16_idx_to_desc ; 
 size_t* pq16_idx_to_field ; 

__attribute__((used)) static dma_addr_t pq16_get_src(struct ioat_raw_descriptor *desc[3], int idx)
{
	struct ioat_raw_descriptor *raw = desc[pq16_idx_to_desc[idx]];

	return raw->field[pq16_idx_to_field[idx]];
}