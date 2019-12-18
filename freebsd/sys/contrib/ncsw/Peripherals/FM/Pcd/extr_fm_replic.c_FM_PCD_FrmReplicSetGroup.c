#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdFrmReplicMember ;
struct TYPE_26__ {int maxNumOfEntries; int numOfEntries; struct TYPE_26__* p_SourceTd; int /*<<< orphan*/  membersList; int /*<<< orphan*/ * nextEngineParams; struct TYPE_26__* h_FmPcd; int /*<<< orphan*/  p_Lock; int /*<<< orphan*/  availableMembersList; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroupParams ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  AddMemberToList (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AllocMember (TYPE_1__*) ; 
 int /*<<< orphan*/  BuildSourceTd (TYPE_1__*) ; 
 scalar_t__ CheckParams (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteGroup (TYPE_1__*) ; 
 scalar_t__ E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_NO_MEMORY ; 
 int FALSE ; 
 scalar_t__ FM_MURAM_AllocMem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int /*<<< orphan*/  FmPcdAcquireLock (TYPE_1__*) ; 
 TYPE_1__* FmPcdGetMuramHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  FmPcdIsAdvancedOffloadSupported (TYPE_1__*) ; 
 scalar_t__ FmPcdUpdateCcShadow (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InitMember (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LinkMemberToMember (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LinkSourceToMember (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_PCD_FrmReplicSetGroup(t_Handle                    h_FmPcd,
                                  t_FmPcdFrmReplicGroupParams *p_ReplicGroupParam)
{
    t_FmPcdFrmReplicGroup       *p_ReplicGroup;
    t_FmPcdFrmReplicMember      *p_CurrentMember, *p_NextMember = NULL;
    int                         i;
    t_Error                     err;
    bool                        last = FALSE;
    t_Handle                    h_Muram;

    SANITY_CHECK_RETURN_VALUE(h_FmPcd, E_INVALID_HANDLE, NULL);
    SANITY_CHECK_RETURN_VALUE(p_ReplicGroupParam, E_INVALID_HANDLE, NULL);

    if (!FmPcdIsAdvancedOffloadSupported(h_FmPcd))
    {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Advanced-offload must be enabled"));
        return NULL;
    }

    err = CheckParams(h_FmPcd, p_ReplicGroupParam);
    if (err)
    {
        REPORT_ERROR(MAJOR, err, (NO_MSG));
        return NULL;
    }

    p_ReplicGroup = (t_FmPcdFrmReplicGroup*)XX_Malloc(sizeof(t_FmPcdFrmReplicGroup));
    if (!p_ReplicGroup)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("No memory"));
        return NULL;
    }
    memset(p_ReplicGroup, 0, sizeof(t_FmPcdFrmReplicGroup));

    /* initialize lists for internal driver use */
    INIT_LIST(&p_ReplicGroup->availableMembersList);
    INIT_LIST(&p_ReplicGroup->membersList);

    p_ReplicGroup->h_FmPcd = h_FmPcd;

    h_Muram = FmPcdGetMuramHandle(p_ReplicGroup->h_FmPcd);
    ASSERT_COND(h_Muram);

    /* initialize the group lock */
    p_ReplicGroup->p_Lock = FmPcdAcquireLock(p_ReplicGroup->h_FmPcd);
    if (!p_ReplicGroup->p_Lock)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Replic group lock"));
        DeleteGroup(p_ReplicGroup);
        return NULL;
    }

    /* Allocate the frame replicator source table descriptor */
    p_ReplicGroup->p_SourceTd =
        (t_Handle)FM_MURAM_AllocMem(h_Muram,
                                    FM_PCD_CC_AD_ENTRY_SIZE,
                                    FM_PCD_CC_AD_TABLE_ALIGN);
    if (!p_ReplicGroup->p_SourceTd)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("frame replicator source table descriptor"));
        DeleteGroup(p_ReplicGroup);
        return NULL;
    }

    /* update the shadow size - required for the host commands */
    err = FmPcdUpdateCcShadow(p_ReplicGroup->h_FmPcd,
                              FM_PCD_CC_AD_ENTRY_SIZE,
                              FM_PCD_CC_AD_TABLE_ALIGN);
    if (err)
    {
        REPORT_ERROR(MAJOR, err, ("Update CC shadow"));
        DeleteGroup(p_ReplicGroup);
        return NULL;
    }

    p_ReplicGroup->maxNumOfEntries  = p_ReplicGroupParam->maxNumOfEntries;

    /* Allocate the maximal number of members ADs and Statistics AD for the group
       It prevents allocation of Muram in run-time */
    for (i=0; i<p_ReplicGroup->maxNumOfEntries; i++)
    {
        err = AllocMember(p_ReplicGroup);
        if (err)
        {
            REPORT_ERROR(MAJOR, err, ("allocate a new member"));
            DeleteGroup(p_ReplicGroup);
            return NULL;
        }
    }

    /* Initialize the members linked lists:
      (hw - the one that is used by the FMan controller and
       sw - the one that is managed by the driver internally) */
    for (i=(p_ReplicGroupParam->numOfEntries-1); i>=0; i--)
    {
        /* check if this is the last member in the group */
        if (i == (p_ReplicGroupParam->numOfEntries-1))
            last = TRUE;
        else
            last = FALSE;

        /* Initialize a new member */
        p_CurrentMember = InitMember(p_ReplicGroup,
                                     &(p_ReplicGroupParam->nextEngineParams[i]),
                                     last);
        if (!p_CurrentMember)
        {
            REPORT_ERROR(MAJOR, E_INVALID_HANDLE, ("No available member"));
            DeleteGroup(p_ReplicGroup);
            return NULL;
        }

        /* Build the members group - link two consecutive members in the hw linked list */
        LinkMemberToMember(p_ReplicGroup, p_CurrentMember, p_NextMember);

        /* update the driver internal members list to be compatible to the hw members linked list */
        AddMemberToList(p_ReplicGroup, p_CurrentMember, &p_ReplicGroup->membersList);

        p_NextMember = p_CurrentMember;
    }

    /* initialize the source table descriptor */
    BuildSourceTd(p_ReplicGroup->p_SourceTd);

    /* link the source table descriptor to point to the first member in the group */
    LinkSourceToMember(p_ReplicGroup, p_ReplicGroup->p_SourceTd, p_NextMember);

    return p_ReplicGroup;
}