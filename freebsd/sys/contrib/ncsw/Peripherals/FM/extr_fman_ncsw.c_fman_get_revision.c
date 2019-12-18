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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/  fm_ip_rev_1; } ;

/* Variables and functions */
 int FPM_REV1_MAJOR_MASK ; 
 int FPM_REV1_MAJOR_SHIFT ; 
 int FPM_REV1_MINOR_MASK ; 
 int FPM_REV1_MINOR_SHIFT ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

void fman_get_revision(struct fman_fpm_regs *fpm_rg,
			uint8_t *major,
			uint8_t *minor)
{
	uint32_t tmp;

	tmp = ioread32be(&fpm_rg->fm_ip_rev_1);
	*major = (uint8_t)((tmp & FPM_REV1_MAJOR_MASK) >> FPM_REV1_MAJOR_SHIFT);
	*minor = (uint8_t)((tmp & FPM_REV1_MINOR_MASK) >> FPM_REV1_MINOR_SHIFT);

}