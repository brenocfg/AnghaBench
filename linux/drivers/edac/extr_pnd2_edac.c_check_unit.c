#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct d_cr_drp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  eccen; } ;

/* Variables and functions */
 scalar_t__ DIMMS_PRESENT (struct d_cr_drp*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 struct d_cr_drp* drp ; 
 TYPE_1__* ecc_ctrl ; 
 int /*<<< orphan*/  pnd2_printk (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int check_unit(int ch)
{
	struct d_cr_drp *d = &drp[ch];

	if (DIMMS_PRESENT(d) && !ecc_ctrl[ch].eccen) {
		pnd2_printk(KERN_INFO, "ECC disabled on channel %d\n", ch);
		return 1;
	}
	return 0;
}