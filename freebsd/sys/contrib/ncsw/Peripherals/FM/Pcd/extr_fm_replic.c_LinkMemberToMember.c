#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {scalar_t__ p_MemberAd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
struct TYPE_10__ {TYPE_3__* h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicGroup ;
struct TYPE_11__ {int physicalMuramBase; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_12__ {int /*<<< orphan*/  res; } ;
typedef  TYPE_4__ t_AdOfTypeResult ;

/* Variables and functions */
 int NEXT_FRM_REPLIC_ADDR_SHIFT ; 
 int NEXT_FRM_REPLIC_MEMBER_INDEX_SHIFT ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int XX_VirtToPhys (TYPE_4__*) ; 

__attribute__((used)) static void LinkMemberToMember(t_FmPcdFrmReplicGroup    *p_ReplicGroup,
                               t_FmPcdFrmReplicMember   *p_CurrentMember,
                               t_FmPcdFrmReplicMember   *p_NextMember)
{
    t_AdOfTypeResult    *p_CurrReplicAd = (t_AdOfTypeResult*)p_CurrentMember->p_MemberAd;
    t_AdOfTypeResult    *p_NextReplicAd = NULL;
    t_FmPcd             *p_FmPcd;
    uint32_t            offset = 0;

    /* Check if the next member exists or it's NULL (- means that this is the last member) */
    if (p_NextMember)
    {
        p_NextReplicAd = (t_AdOfTypeResult*)p_NextMember->p_MemberAd;
        p_FmPcd = p_ReplicGroup->h_FmPcd;
        offset = (XX_VirtToPhys(p_NextReplicAd) - (p_FmPcd->physicalMuramBase));
        offset = ((offset>>NEXT_FRM_REPLIC_ADDR_SHIFT)<< NEXT_FRM_REPLIC_MEMBER_INDEX_SHIFT);
    }

    /* link the current AD to point to the AD of the next member */
    WRITE_UINT32(p_CurrReplicAd->res, offset);
}