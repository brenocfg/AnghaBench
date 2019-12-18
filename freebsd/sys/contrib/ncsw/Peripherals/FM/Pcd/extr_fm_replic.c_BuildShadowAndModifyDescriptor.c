#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* p_MemberAd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
struct TYPE_22__ {int /*<<< orphan*/  shadowLock; struct TYPE_22__* p_CcShadow; struct TYPE_22__* p_SourceTd; int /*<<< orphan*/  h_ShadowSpinlock; struct TYPE_22__* h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicGroup ;
typedef  TYPE_2__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  BuildSourceTd (TYPE_2__*) ; 
 scalar_t__ ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FillReplicAdOfTypeResult (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IO2IOCpy32 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LinkMemberToMember (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LinkSourceToMember (TYPE_2__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ ModifyDescriptor (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  TRY_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static t_Error BuildShadowAndModifyDescriptor(t_FmPcdFrmReplicGroup   *p_ReplicGroup,
                                              t_FmPcdFrmReplicMember  *p_NextMember,
                                              t_FmPcdFrmReplicMember  *p_CurrentMember,
                                              bool                    sourceDescriptor,
                                              bool                    last)
{
    t_FmPcd                 *p_FmPcd;
    t_FmPcdFrmReplicMember  shadowMember;
    t_Error                 err;

    ASSERT_COND(p_ReplicGroup);
    ASSERT_COND(p_ReplicGroup->h_FmPcd);

    p_FmPcd = p_ReplicGroup->h_FmPcd;
    ASSERT_COND(p_FmPcd->p_CcShadow);

    if (!TRY_LOCK(p_FmPcd->h_ShadowSpinlock, &p_FmPcd->shadowLock))
        return ERROR_CODE(E_BUSY);

    if (sourceDescriptor)
    {
        BuildSourceTd(p_FmPcd->p_CcShadow);
        LinkSourceToMember(p_ReplicGroup, p_FmPcd->p_CcShadow, p_NextMember);

        /* Modify the source table descriptor according to the prepared shadow descriptor */
        err = ModifyDescriptor(p_ReplicGroup,
                               p_ReplicGroup->p_SourceTd,
                               p_FmPcd->p_CcShadow/* new prepared source td */);

        RELEASE_LOCK(p_FmPcd->shadowLock);
        if (err)
            RETURN_ERROR(MAJOR, err, ("Modify source Descriptor in BuildShadowAndModifyDescriptor"));

    }
    else
    {
        IO2IOCpy32(p_FmPcd->p_CcShadow,
                   p_CurrentMember->p_MemberAd,
                   FM_PCD_CC_AD_ENTRY_SIZE);

        /* update the last bit in the shadow ad */
        FillReplicAdOfTypeResult(p_FmPcd->p_CcShadow, last);

        shadowMember.p_MemberAd = p_FmPcd->p_CcShadow;

        /* update the next FR member index */
        LinkMemberToMember(p_ReplicGroup, &shadowMember, p_NextMember);

        /* Modify the next member according to the prepared shadow descriptor */
        err = ModifyDescriptor(p_ReplicGroup,
                               p_CurrentMember->p_MemberAd,
                               p_FmPcd->p_CcShadow);

        RELEASE_LOCK(p_FmPcd->shadowLock);
        if (err)
            RETURN_ERROR(MAJOR, err, ("Modify Descriptor in BuildShadowAndModifyDescriptor"));
    }


    return E_OK;
}