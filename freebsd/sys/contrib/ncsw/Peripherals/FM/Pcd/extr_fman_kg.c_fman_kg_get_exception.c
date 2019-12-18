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
struct fman_kg_regs {int /*<<< orphan*/  fmkg_eer; int /*<<< orphan*/  fmkg_seer; int /*<<< orphan*/  fmkg_seeer; int /*<<< orphan*/  fmkg_eeer; } ;

/* Variables and functions */
 int FM_EX_KG_KEYSIZE_OVERFLOW ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_kg_get_exception(struct fman_kg_regs *regs,
				uint32_t *events,
				uint32_t *scheme_ids,
				bool clear)
{
	uint32_t mask;

	*events = ioread32be(&regs->fmkg_eer);
	mask = ioread32be(&regs->fmkg_eeer);
	*events &= mask;
 
	*scheme_ids = 0;

	if (*events & FM_EX_KG_KEYSIZE_OVERFLOW) {
		*scheme_ids = ioread32be(&regs->fmkg_seer);
		mask = ioread32be(&regs->fmkg_seeer);
		*scheme_ids &= mask;
	}

	if (clear) {
		iowrite32be(*scheme_ids, &regs->fmkg_seer);
		iowrite32be(*events, &regs->fmkg_eer);
	}
}