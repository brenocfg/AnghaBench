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
struct iop_adma_desc_slot {int /*<<< orphan*/  hw_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  iop3xx_desc_init_xor (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static inline void
iop_desc_init_xor(struct iop_adma_desc_slot *desc, int src_cnt,
		  unsigned long flags)
{
	iop3xx_desc_init_xor(desc->hw_desc, src_cnt, flags);
}