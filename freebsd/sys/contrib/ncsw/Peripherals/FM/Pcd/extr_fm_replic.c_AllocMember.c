#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_1__* t_Handle ;
struct TYPE_11__ {int /*<<< orphan*/  node; int /*<<< orphan*/ * p_MemberAd; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicMember ;
struct TYPE_10__ {int /*<<< orphan*/  availableMembersList; int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_AdOfTypeResult ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MURAM_AllocMem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 TYPE_1__* FmPcdGetMuramHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_AddToTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error AllocMember(t_FmPcdFrmReplicGroup *p_ReplicGroup)
{
    t_FmPcdFrmReplicMember  *p_CurrentMember;
    t_Handle                h_Muram;

    ASSERT_COND(p_ReplicGroup);

    h_Muram = FmPcdGetMuramHandle(p_ReplicGroup->h_FmPcd);
    ASSERT_COND(h_Muram);

    /* Initialize an internal structure of a member to add to the available members list */
    p_CurrentMember = (t_FmPcdFrmReplicMember *)XX_Malloc(sizeof(t_FmPcdFrmReplicMember));
    if (!p_CurrentMember)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("Frame replicator member"));

    memset(p_CurrentMember, 0 ,sizeof(t_FmPcdFrmReplicMember));

    /* Allocate the member AD */
    p_CurrentMember->p_MemberAd =
        (t_AdOfTypeResult*)FM_MURAM_AllocMem(h_Muram,
                                             FM_PCD_CC_AD_ENTRY_SIZE,
                                             FM_PCD_CC_AD_TABLE_ALIGN);
    if (!p_CurrentMember->p_MemberAd)
    {
        XX_Free(p_CurrentMember);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("member AD table"));
    }
    IOMemSet32((uint8_t*)p_CurrentMember->p_MemberAd, 0, FM_PCD_CC_AD_ENTRY_SIZE);

    /* Add the new member to the available members list */
    LIST_AddToTail(&p_CurrentMember->node, &(p_ReplicGroup->availableMembersList));

    return E_OK;
}