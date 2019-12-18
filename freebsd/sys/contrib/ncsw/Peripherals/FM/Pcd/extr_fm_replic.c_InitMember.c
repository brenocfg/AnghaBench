#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {scalar_t__ p_MemberAd; int /*<<< orphan*/ * h_Manip; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
struct TYPE_12__ {int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicGroup ;
struct TYPE_13__ {int /*<<< orphan*/ * h_Manip; } ;
typedef  TYPE_3__ t_FmPcdCcNextEngineParams ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  E_NOT_FOUND ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FillReplicAdOfTypeResult (scalar_t__,int) ; 
 TYPE_1__* GetAvailableMember (TYPE_2__*) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NextStepAd (scalar_t__,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_FmPcdFrmReplicMember* InitMember(t_FmPcdFrmReplicGroup     *p_ReplicGroup,
                                          t_FmPcdCcNextEngineParams *p_MemberParams,
                                          bool                      last)
{
    t_FmPcdFrmReplicMember  *p_CurrentMember = NULL;

    ASSERT_COND(p_ReplicGroup);

    /* Get an available member from the internal members list */
    p_CurrentMember = GetAvailableMember(p_ReplicGroup);
    if (!p_CurrentMember)
    {
        REPORT_ERROR(MAJOR, E_NOT_FOUND, ("Available member"));
        return NULL;
    }
    p_CurrentMember->h_Manip = NULL;

    /* clear the Ad of the new member */
    IOMemSet32((uint8_t*)p_CurrentMember->p_MemberAd, 0, FM_PCD_CC_AD_ENTRY_SIZE);

    INIT_LIST(&p_CurrentMember->node);

    /* Initialize the Ad of the member */
    NextStepAd(p_CurrentMember->p_MemberAd,
               NULL,
               p_MemberParams,
               p_ReplicGroup->h_FmPcd);

    /* save Manip handle (for free needs) */
    if (p_MemberParams->h_Manip)
        p_CurrentMember->h_Manip = p_MemberParams->h_Manip;

    /* Initialize the relevant frame replicator fields in the AD */
    FillReplicAdOfTypeResult(p_CurrentMember->p_MemberAd, last);

    return p_CurrentMember;
}