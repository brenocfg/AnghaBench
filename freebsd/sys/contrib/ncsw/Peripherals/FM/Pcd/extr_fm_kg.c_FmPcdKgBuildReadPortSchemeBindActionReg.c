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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int FM_KG_KGAR_GO ; 
 int FM_KG_KGAR_READ ; 
 int FM_PCD_KG_KGAR_SEL_PORT_ENTRY ; 
 int FM_PCD_KG_KGAR_SEL_PORT_WSEL_SP ; 

uint32_t FmPcdKgBuildReadPortSchemeBindActionReg(uint8_t hardwarePortId)
{

    return (uint32_t)(FM_KG_KGAR_GO |
                      FM_KG_KGAR_READ |
                      FM_PCD_KG_KGAR_SEL_PORT_ENTRY |
                      hardwarePortId |
                      FM_PCD_KG_KGAR_SEL_PORT_WSEL_SP);
}