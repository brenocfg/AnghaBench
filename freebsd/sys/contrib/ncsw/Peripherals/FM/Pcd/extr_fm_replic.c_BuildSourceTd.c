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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcAndOffsets; int /*<<< orphan*/  ccAdBase; } ;
typedef  TYPE_1__ t_AdOfTypeContLookup ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (void*) ; 
 int /*<<< orphan*/  FM_PCD_AD_CONT_LOOKUP_TYPE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FRM_REPLIC_SOURCE_TD_OPCODE ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BuildSourceTd(void *p_Ad)
{
    t_AdOfTypeContLookup    *p_SourceTd;

    ASSERT_COND(p_Ad);

    p_SourceTd = (t_AdOfTypeContLookup *)p_Ad;

    IOMemSet32((uint8_t*)p_SourceTd, 0, FM_PCD_CC_AD_ENTRY_SIZE);

    /* initialize the source table descriptor */
    WRITE_UINT32(p_SourceTd->ccAdBase,     FM_PCD_AD_CONT_LOOKUP_TYPE);
    WRITE_UINT32(p_SourceTd->pcAndOffsets, FRM_REPLIC_SOURCE_TD_OPCODE);
}