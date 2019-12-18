#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_5__ {int /*<<< orphan*/  p_SourceTd; TYPE_2__* h_FmPcd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;
struct TYPE_6__ {scalar_t__ physicalMuramBase; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_7__ {int /*<<< orphan*/  fqid; } ;
typedef  TYPE_3__ t_AdOfTypeResult ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int FM_PCD_AD_BYPASS_TYPE ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

void FrmReplicGroupUpdateAd(t_Handle  h_ReplicGroup,
                            void      *p_Ad,
                            t_Handle  *h_AdNew)
{
    t_FmPcdFrmReplicGroup   *p_ReplicGroup = (t_FmPcdFrmReplicGroup *)h_ReplicGroup;
    t_AdOfTypeResult    *p_AdResult = (t_AdOfTypeResult*)p_Ad;
    t_FmPcd             *p_FmPcd;

    ASSERT_COND(p_ReplicGroup);
    p_FmPcd = p_ReplicGroup->h_FmPcd;

    /* build a bypass ad */
    WRITE_UINT32(p_AdResult->fqid, FM_PCD_AD_BYPASS_TYPE |
        (uint32_t)((XX_VirtToPhys(p_ReplicGroup->p_SourceTd)) - p_FmPcd->physicalMuramBase));

    *h_AdNew = NULL;
}