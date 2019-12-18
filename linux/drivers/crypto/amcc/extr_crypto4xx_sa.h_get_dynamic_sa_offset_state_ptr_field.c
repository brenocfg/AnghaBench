#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int key_size; int inner_size; int outer_size; int spi; int seq_num0; int seq_num1; int seq_num_mask0; int seq_num_mask1; int seq_num_mask2; int seq_num_mask3; int iv0; int iv1; int iv2; int iv3; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct dynamic_sa_ctl {TYPE_2__ sa_contents; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
get_dynamic_sa_offset_state_ptr_field(struct dynamic_sa_ctl *cts)
{
	u32 offset;

	offset = cts->sa_contents.bf.key_size
		+ cts->sa_contents.bf.inner_size
		+ cts->sa_contents.bf.outer_size
		+ cts->sa_contents.bf.spi
		+ cts->sa_contents.bf.seq_num0
		+ cts->sa_contents.bf.seq_num1
		+ cts->sa_contents.bf.seq_num_mask0
		+ cts->sa_contents.bf.seq_num_mask1
		+ cts->sa_contents.bf.seq_num_mask2
		+ cts->sa_contents.bf.seq_num_mask3
		+ cts->sa_contents.bf.iv0
		+ cts->sa_contents.bf.iv1
		+ cts->sa_contents.bf.iv2
		+ cts->sa_contents.bf.iv3;

	return sizeof(struct dynamic_sa_ctl) + offset * 4;
}