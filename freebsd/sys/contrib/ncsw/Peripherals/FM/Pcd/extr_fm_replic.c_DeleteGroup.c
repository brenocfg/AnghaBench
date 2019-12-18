#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  TYPE_1__* t_Handle ;
struct TYPE_19__ {int numOfEntries; int maxNumOfEntries; scalar_t__ p_Lock; struct TYPE_19__* h_FmPcd; int /*<<< orphan*/ * p_MemberAd; int /*<<< orphan*/ * h_Manip; int /*<<< orphan*/ * p_SourceTd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* FmPcdGetMuramHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  FmPcdManipUpdateOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdReleaseLock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  FreeMember (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* GetAvailableMember (TYPE_1__*) ; 
 TYPE_1__* GetMemberByIndex (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveMemberFromList (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 

__attribute__((used)) static void DeleteGroup(t_FmPcdFrmReplicGroup *p_ReplicGroup)
{
    int                     i, j;
    t_Handle                h_Muram;
    t_FmPcdFrmReplicMember  *p_Member, *p_CurrentMember;

    if (p_ReplicGroup)
    {
        ASSERT_COND(p_ReplicGroup->h_FmPcd);
        h_Muram = FmPcdGetMuramHandle(p_ReplicGroup->h_FmPcd);
        ASSERT_COND(h_Muram);

        /* free the source table descriptor */
        if (p_ReplicGroup->p_SourceTd)
        {
            FM_MURAM_FreeMem(h_Muram, p_ReplicGroup->p_SourceTd);
            p_ReplicGroup->p_SourceTd = NULL;
        }

        /* Remove all members from the members linked list (hw and sw) and
           return the members to the available members list */
        if (p_ReplicGroup->numOfEntries)
        {
            j = p_ReplicGroup->numOfEntries-1;

            /* manually removal of the member because there are no owners of
               this group */
            for (i=j; i>=0; i--)
            {
                p_CurrentMember = GetMemberByIndex(p_ReplicGroup, (uint16_t)i/*memberIndex*/);
                ASSERT_COND(p_CurrentMember);

                if (p_CurrentMember->h_Manip)
                {
                    FmPcdManipUpdateOwner(p_CurrentMember->h_Manip, FALSE);
                    p_CurrentMember->h_Manip = NULL;
                }

                /* remove the member from the internal driver members list */
                RemoveMemberFromList(p_ReplicGroup, p_CurrentMember);

                /* return the member to the available members list */
                FreeMember(p_ReplicGroup, p_CurrentMember);
            }
        }

        /* Free members AD */
        for (i=0; i<p_ReplicGroup->maxNumOfEntries; i++)
        {
            p_Member = GetAvailableMember(p_ReplicGroup);
            ASSERT_COND(p_Member);
            if (p_Member->p_MemberAd)
            {
                FM_MURAM_FreeMem(h_Muram, p_Member->p_MemberAd);
                p_Member->p_MemberAd = NULL;
            }
            XX_Free(p_Member);
        }

        /* release the group lock */
        if (p_ReplicGroup->p_Lock)
            FmPcdReleaseLock(p_ReplicGroup->h_FmPcd, p_ReplicGroup->p_Lock);

        /* free the replicator group */
        XX_Free(p_ReplicGroup);
    }
}