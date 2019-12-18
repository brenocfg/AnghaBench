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
struct fman_kg_regs {int /*<<< orphan*/  fmkg_seer; int /*<<< orphan*/  fmkg_eer; int /*<<< orphan*/  fmkg_feer; int /*<<< orphan*/  fmkg_seeer; int /*<<< orphan*/  fmkg_eeer; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_kg_get_event(struct fman_kg_regs *regs,
			uint32_t *event,
			uint32_t *scheme_idx)
{
	uint32_t mask, force;

	*event = ioread32be(&regs->fmkg_eer);
	mask = ioread32be(&regs->fmkg_eeer);
	*scheme_idx = ioread32be(&regs->fmkg_seer);
	*scheme_idx &= ioread32be(&regs->fmkg_seeer);

	*event &= mask;

	/* clear the forced events */
	force = ioread32be(&regs->fmkg_feer);
	if (force & *event)
		iowrite32be(force & ~*event ,&regs->fmkg_feer);

	iowrite32be(*event, &regs->fmkg_eer);
	iowrite32be(*scheme_idx, &regs->fmkg_seer);
}