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
struct fman_kg_regs {int /*<<< orphan*/  fmkg_tpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_kg_get_schemes_total_counter(struct fman_kg_regs *regs)
{
    return ioread32be(&regs->fmkg_tpc);
}