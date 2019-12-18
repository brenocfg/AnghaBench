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

/* Variables and functions */
 unsigned int MSR_SMCA_MC_CTL (int) ; 

__attribute__((used)) static unsigned int
mca_smca_ctl_reg(int bank)
{
        return (MSR_SMCA_MC_CTL(bank));
}