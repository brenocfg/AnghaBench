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
struct extra_reg {scalar_t__ idx; int event; } ;

/* Variables and functions */
 scalar_t__ EXTRA_REG_NHMEX_M_ZDP_CTL_FVC ; 
 int NHMEX_M_PMON_CTL_INC_SEL_SHIFT ; 

__attribute__((used)) static int nhmex_mbox_extra_reg_idx(struct extra_reg *er)
{
	if (er->idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC)
		return er->idx;
	return er->idx + (er->event >> NHMEX_M_PMON_CTL_INC_SEL_SHIFT) - 0xd;
}