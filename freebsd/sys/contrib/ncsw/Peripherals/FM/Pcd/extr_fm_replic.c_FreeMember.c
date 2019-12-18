#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_MemberAd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
typedef  int /*<<< orphan*/  t_FmPcdFrmReplicGroup ;

/* Variables and functions */
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutAvailableMember (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void FreeMember(t_FmPcdFrmReplicGroup    *p_ReplicGroup,
                       t_FmPcdFrmReplicMember   *p_Member)
{
    /* Note: Can't free the member AD just returns the member to the available
       member list - therefore only memset the AD */

    /* zero the AD */
    IOMemSet32(p_Member->p_MemberAd, 0, FM_PCD_CC_AD_ENTRY_SIZE);


    /* return the member to the available members list */
    PutAvailableMember(p_ReplicGroup, p_Member);
}