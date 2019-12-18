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
typedef  int uint32_t ;
struct tgec_regs {int /*<<< orphan*/  hashtable_ctrl; } ;

/* Variables and functions */
 int TGEC_HASH_MCAST_EN ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_tgec_reset_filter_table(struct tgec_regs *regs)
{
	uint32_t i;
	for (i = 0; i < 512; i++)
		iowrite32be(i & ~TGEC_HASH_MCAST_EN, &regs->hashtable_ctrl);
}