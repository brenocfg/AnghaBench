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
struct fman_kg_regs {int /*<<< orphan*/  fmkg_seeer; int /*<<< orphan*/  fmkg_seer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_kg_enable_scheme_interrupts(struct fman_kg_regs *regs)
{
	/* enable and enable all scheme interrupts */
	iowrite32be(0xFFFFFFFF, &regs->fmkg_seer);
	iowrite32be(0xFFFFFFFF, &regs->fmkg_seeer);
}