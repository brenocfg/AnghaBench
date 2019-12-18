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

/* Variables and functions */
 int /*<<< orphan*/  FM_PCD_PLCR_PAR_PWSEL_PEGNIA ; 
 int /*<<< orphan*/  FM_PCD_PLCR_PAR_PWSEL_PERNIA ; 
 int /*<<< orphan*/  FM_PCD_PLCR_PAR_PWSEL_PEYNIA ; 

uint32_t FmPcdPlcrBuildNiaProfileReg(bool green, bool yellow, bool red)
{

    uint32_t tmpReg32 = 0;

    if (green)
        tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PEGNIA;
    if (yellow)
        tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PEYNIA;
    if (red)
        tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PERNIA;

    return tmpReg32;
}