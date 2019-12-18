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
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_5__ {scalar_t__ h_FmPcd; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;
struct TYPE_6__ {scalar_t__ maxNumOfKeys; scalar_t__ h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdCcNode ;
struct TYPE_7__ {int /*<<< orphan*/ * p_CcShadow; } ;
typedef  TYPE_3__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ FM_MURAM_AllocMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (TYPE_3__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static __inline__ t_Handle GetNewAd(t_Handle h_FmPcdCcNodeOrTree, bool isTree)
{
    t_FmPcd *p_FmPcd;
    t_Handle h_Ad;

    if (isTree)
        p_FmPcd = (t_FmPcd *)(((t_FmPcdCcTree *)h_FmPcdCcNodeOrTree)->h_FmPcd);
    else
        p_FmPcd = (t_FmPcd *)(((t_FmPcdCcNode *)h_FmPcdCcNodeOrTree)->h_FmPcd);

    if ((isTree && p_FmPcd->p_CcShadow)
            || (!isTree && ((t_FmPcdCcNode *)h_FmPcdCcNodeOrTree)->maxNumOfKeys))
    {
        /* The allocated shadow is divided as follows:
         0 . . .       16 . . .
         ---------------------------------------------------
         |   Shadow   |   Shadow Keys   |   Shadow Next    |
         |     Ad     |   Match Table   |   Engine Table   |
         | (16 bytes) | (maximal size)  |  (maximal size)  |
         ---------------------------------------------------
         */
        if (!p_FmPcd->p_CcShadow)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("CC Shadow not allocated"));
            return NULL;
        }

        h_Ad = p_FmPcd->p_CcShadow;
    }
    else
    {
        h_Ad = (t_Handle)FM_MURAM_AllocMem(FmPcdGetMuramHandle(p_FmPcd),
                                           FM_PCD_CC_AD_ENTRY_SIZE,
                                           FM_PCD_CC_AD_TABLE_ALIGN);
        if (!h_Ad)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for CC node action descriptor"));
            return NULL;
        }
    }

    return h_Ad;
}