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

/* Variables and functions */
 int FALSE ; 
 int FM_PCD_PLCR_PEMODE_PI ; 
 int TRUE ; 

bool    FmPcdPlcrHwProfileIsValid(uint32_t profileModeReg)
{

    if (profileModeReg & FM_PCD_PLCR_PEMODE_PI)
        return TRUE;
    else
        return FALSE;
}