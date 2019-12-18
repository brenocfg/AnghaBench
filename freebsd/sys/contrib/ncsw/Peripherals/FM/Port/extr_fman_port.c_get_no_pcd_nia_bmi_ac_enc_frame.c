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
struct fman_port_cfg {scalar_t__ errata_A006675; } ;

/* Variables and functions */
 int NIA_BMI_AC_ENQ_FRAME ; 
 int NIA_ENG_BMI ; 
 int NIA_ENG_FM_CTL ; 
 int NIA_FM_CTL_AC_NO_IPACC_PRE_BMI_ENQ_FRAME ; 

__attribute__((used)) static uint32_t get_no_pcd_nia_bmi_ac_enc_frame(struct fman_port_cfg *cfg)
{
    if (cfg->errata_A006675)
        return NIA_ENG_FM_CTL |
            NIA_FM_CTL_AC_NO_IPACC_PRE_BMI_ENQ_FRAME;
    else
        return NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME;
}