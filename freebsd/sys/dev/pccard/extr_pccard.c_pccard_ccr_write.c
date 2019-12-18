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
struct pccard_function {int ccr_mask; scalar_t__ pf_ccr_offset; int /*<<< orphan*/  pf_ccrh; int /*<<< orphan*/  pf_ccrt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
pccard_ccr_write(struct pccard_function *pf, int ccr, int val)
{
	if ((pf->ccr_mask) & (1 << (ccr / 2))) {
		bus_space_write_1(pf->pf_ccrt, pf->pf_ccrh,
		    pf->pf_ccr_offset + ccr, val);
	}
}