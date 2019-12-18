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
struct TYPE_4__ {int /*<<< orphan*/  fmPortsLst; scalar_t__ ccTreeBaseAddr; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;
typedef  int /*<<< orphan*/  t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseLst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 

__attribute__((used)) static void DeleteTree(t_FmPcdCcTree *p_FmPcdTree, t_FmPcd *p_FmPcd)
{
    if (p_FmPcdTree)
    {
        if (p_FmPcdTree->ccTreeBaseAddr)
        {
            FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_FmPcd),
                             UINT_TO_PTR(p_FmPcdTree->ccTreeBaseAddr));
            p_FmPcdTree->ccTreeBaseAddr = 0;
        }

        ReleaseLst(&p_FmPcdTree->fmPortsLst);

        XX_Free(p_FmPcdTree);
    }
}