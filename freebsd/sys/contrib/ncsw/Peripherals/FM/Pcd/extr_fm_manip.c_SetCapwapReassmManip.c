#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {scalar_t__ h_Ad; } ;
struct TYPE_7__ {TYPE_2__ capwap; int /*<<< orphan*/  dataMemId; } ;
struct TYPE_9__ {TYPE_1__ reassmParams; scalar_t__ h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int /*<<< orphan*/  FillReassmManipParams (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_TYPE_CAPWAP ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ReleaseManipHandler (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XX_MallocSmart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error SetCapwapReassmManip(t_FmPcdManip *p_Manip)
{
    t_FmPcd *p_FmPcd = (t_FmPcd *)p_Manip->h_FmPcd;

    /* Allocation if CAPWAP Action descriptor */
    p_Manip->reassmParams.capwap.h_Ad = (t_Handle)XX_MallocSmart(
            FM_PCD_CC_AD_ENTRY_SIZE, p_Manip->reassmParams.dataMemId,
            FM_PCD_CC_AD_TABLE_ALIGN);
    if (!p_Manip->reassmParams.capwap.h_Ad)
    {
        ReleaseManipHandler(p_Manip, p_FmPcd);
        RETURN_ERROR(MAJOR, E_NO_MEMORY,
                     ("Allocation of CAPWAP table descriptor"));
    }

    memset(p_Manip->reassmParams.capwap.h_Ad, 0, FM_PCD_CC_AD_ENTRY_SIZE);

    /* Fill reassembly manipulation parameter in the Reassembly Action Descriptor */
    return FillReassmManipParams(p_Manip, HEADER_TYPE_CAPWAP);
}