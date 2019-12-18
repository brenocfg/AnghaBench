#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_23__ {int /*<<< orphan*/  node; int /*<<< orphan*/  p_MemberAd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
struct TYPE_24__ {scalar_t__ numOfEntries; scalar_t__ maxNumOfEntries; int /*<<< orphan*/  membersList; int /*<<< orphan*/  p_SourceTd; int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicGroup ;
typedef  TYPE_2__ t_FmPcdCcNextEngineParams ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  AddMemberToList (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_CODE (scalar_t__) ; 
 scalar_t__ E_BUSY ; 
 scalar_t__ E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_SELECTION ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES ; 
#define  FRM_REPLIC_FIRST_MEMBER_INDEX 130 
#define  FRM_REPLIC_LAST_MEMBER_INDEX 129 
#define  FRM_REPLIC_MIDDLE_MEMBER_INDEX 128 
 int /*<<< orphan*/  FillReplicAdOfTypeResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FrmReplicGroupTryLock (TYPE_2__*) ; 
 int /*<<< orphan*/  FrmReplicGroupUnlock (TYPE_2__*) ; 
 scalar_t__ GET_ERROR_TYPE (scalar_t__) ; 
 TYPE_1__* GetMemberByIndex (TYPE_2__*,scalar_t__) ; 
 int GetMemberPosition (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* InitMember (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LinkMemberToMember (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LinkSourceToMember (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MemberCheckParams (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

t_Error FM_PCD_FrmReplicAddMember(t_Handle                  h_ReplicGroup,
                                  uint16_t                  memberIndex,
                                  t_FmPcdCcNextEngineParams *p_MemberParams)
{
    t_FmPcdFrmReplicGroup       *p_ReplicGroup = (t_FmPcdFrmReplicGroup*) h_ReplicGroup;
    t_FmPcdFrmReplicMember      *p_NewMember, *p_CurrentMember = NULL, *p_PreviousMember = NULL;
    t_Error                     err;
    uint8_t                     memberPosition;

    SANITY_CHECK_RETURN_ERROR(p_ReplicGroup, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_MemberParams, E_INVALID_HANDLE);

    /* group lock */
    err = FrmReplicGroupTryLock(p_ReplicGroup);
    if (GET_ERROR_TYPE(err) == E_BUSY)
        return ERROR_CODE(E_BUSY);

    if (memberIndex > p_ReplicGroup->numOfEntries)
    {
        /* unlock */
        FrmReplicGroupUnlock(p_ReplicGroup);
        RETURN_ERROR(MAJOR, E_INVALID_SELECTION,
                     ("memberIndex is greater than the members in the list"));
    }

    if (memberIndex >= p_ReplicGroup->maxNumOfEntries)
    {
        /* unlock */
        FrmReplicGroupUnlock(p_ReplicGroup);
        RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("memberIndex is greater than the allowed number of members in the group"));
    }

    if ((p_ReplicGroup->numOfEntries + 1) > FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES)
    {
        /* unlock */
        FrmReplicGroupUnlock(p_ReplicGroup);
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("numOfEntries with new entry can not be larger than %d\n",
                      FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES));
    }

    err = MemberCheckParams(p_ReplicGroup->h_FmPcd, p_MemberParams);
    if (err)
    {
        /* unlock */
        FrmReplicGroupUnlock(p_ReplicGroup);
        RETURN_ERROR(MAJOR, err, ("member check parameters in add operation"));
    }
    /* determine the member position in the group */
    memberPosition = GetMemberPosition(p_ReplicGroup,
                                       memberIndex,
                                       TRUE/* add operation */);

    /* Initialize a new member */
    p_NewMember = InitMember(p_ReplicGroup,
                             p_MemberParams,
                             (memberPosition == FRM_REPLIC_LAST_MEMBER_INDEX ? TRUE : FALSE));
    if (!p_NewMember)
    {
        /* unlock */
        FrmReplicGroupUnlock(p_ReplicGroup);
        RETURN_ERROR(MAJOR, E_INVALID_HANDLE, ("No available member"));
    }

    switch (memberPosition)
    {
        case FRM_REPLIC_FIRST_MEMBER_INDEX:
            p_CurrentMember = GetMemberByIndex(p_ReplicGroup, memberIndex);
            ASSERT_COND(p_CurrentMember);

            LinkMemberToMember(p_ReplicGroup, p_NewMember, p_CurrentMember);

            /* update the internal group source TD */
            LinkSourceToMember(p_ReplicGroup,
                               p_ReplicGroup->p_SourceTd,
                               p_NewMember);

            /* add member to the internal sw member list */
            AddMemberToList(p_ReplicGroup,
                            p_NewMember,
                            &p_ReplicGroup->membersList);
            break;

        case FRM_REPLIC_MIDDLE_MEMBER_INDEX:
            p_CurrentMember = GetMemberByIndex(p_ReplicGroup, memberIndex);
            ASSERT_COND(p_CurrentMember);

            p_PreviousMember = GetMemberByIndex(p_ReplicGroup, (uint16_t)(memberIndex-1));
            ASSERT_COND(p_PreviousMember);

            LinkMemberToMember(p_ReplicGroup, p_NewMember, p_CurrentMember);
            LinkMemberToMember(p_ReplicGroup, p_PreviousMember, p_NewMember);

            AddMemberToList(p_ReplicGroup, p_NewMember, &p_PreviousMember->node);
            break;

        case FRM_REPLIC_LAST_MEMBER_INDEX:
            p_PreviousMember = GetMemberByIndex(p_ReplicGroup, (uint16_t)(memberIndex-1));
            ASSERT_COND(p_PreviousMember);

            LinkMemberToMember(p_ReplicGroup, p_PreviousMember, p_NewMember);
            FillReplicAdOfTypeResult(p_PreviousMember->p_MemberAd, FALSE/*last*/);

            /* add the new member to the internal sw member list */
            AddMemberToList(p_ReplicGroup, p_NewMember, &p_PreviousMember->node);
           break;

        default:
            /* unlock */
            FrmReplicGroupUnlock(p_ReplicGroup);
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("member position in add member"));

    }

    /* unlock */
    FrmReplicGroupUnlock(p_ReplicGroup);

    return E_OK;
}