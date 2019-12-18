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
struct memac_regs {int /*<<< orphan*/  statn_config; } ;

/* Variables and functions */
 int STATS_CFG_CLR ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_memac_reset_stat(struct memac_regs *regs)
{
    uint32_t tmp;

    tmp = ioread32be(&regs->statn_config);

    tmp |= STATS_CFG_CLR;

    iowrite32be(tmp, &regs->statn_config);

    while (ioread32be(&regs->statn_config) & STATS_CFG_CLR);
}