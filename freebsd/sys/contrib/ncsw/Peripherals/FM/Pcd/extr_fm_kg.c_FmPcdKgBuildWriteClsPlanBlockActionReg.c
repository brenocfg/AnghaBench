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

/* Variables and functions */
 int DUMMY_PORT_ID ; 
 int FM_KG_KGAR_GO ; 
 int FM_KG_KGAR_WRITE ; 
 int FM_PCD_KG_KGAR_NUM_SHIFT ; 
 int FM_PCD_KG_KGAR_SEL_CLS_PLAN_ENTRY ; 
 int FM_PCD_KG_KGAR_WSEL_MASK ; 

uint32_t FmPcdKgBuildWriteClsPlanBlockActionReg(uint8_t grpId)
{
    return (uint32_t)(FM_KG_KGAR_GO |
                      FM_KG_KGAR_WRITE |
                      FM_PCD_KG_KGAR_SEL_CLS_PLAN_ENTRY |
                      DUMMY_PORT_ID |
                      ((uint32_t)grpId << FM_PCD_KG_KGAR_NUM_SHIFT) |
                      FM_PCD_KG_KGAR_WSEL_MASK);

    /* if we ever want to write 1 by 1, use:
       sel = (uint8_t)(0x01 << (7- (entryId % CLS_PLAN_NUM_PER_GRP)));
     */
}