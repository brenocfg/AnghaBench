#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {scalar_t__ physicalMuramBase; int /*<<< orphan*/  p_MemberAd; int /*<<< orphan*/  matchTblPtr; struct TYPE_9__* h_FmPcd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;
typedef  TYPE_1__ t_FmPcd ;
typedef  TYPE_1__ t_AdOfTypeContLookup ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LinkSourceToMember(t_FmPcdFrmReplicGroup    *p_ReplicGroup,
                               t_AdOfTypeContLookup     *p_SourceTd,
                               t_FmPcdFrmReplicMember   *p_ReplicMember)
{
    t_FmPcd             *p_FmPcd;

    ASSERT_COND(p_SourceTd);
    ASSERT_COND(p_ReplicMember);
    ASSERT_COND(p_ReplicGroup);
    ASSERT_COND(p_ReplicGroup->h_FmPcd);

    /* Link the first member in the group to the source TD */
    p_FmPcd = p_ReplicGroup->h_FmPcd;

    WRITE_UINT32(p_SourceTd->matchTblPtr,
        (uint32_t)(XX_VirtToPhys(p_ReplicMember->p_MemberAd) -
                        p_FmPcd->physicalMuramBase));
}