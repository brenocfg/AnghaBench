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
struct fman_fpm_regs {int /*<<< orphan*/  fm_npi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_get_normal_pending(struct fman_fpm_regs *fpm_rg)
{
	return ioread32be(&fpm_rg->fm_npi);
}