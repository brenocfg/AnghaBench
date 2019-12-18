#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  ccTreeBaseAddr; int /*<<< orphan*/  numOfEntries; int /*<<< orphan*/  keyAndNextEngineParams; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  CcUpdateParam (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UINT_TO_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error CcUpdateParams(t_Handle h_FmPcd, t_Handle h_PcdParams,
                              t_Handle h_FmPort, t_Handle h_FmTree,
                              bool validate)
{
    t_FmPcdCcTree *p_CcTree = (t_FmPcdCcTree *)h_FmTree;

    return CcUpdateParam(h_FmPcd, h_PcdParams, h_FmPort,
                         p_CcTree->keyAndNextEngineParams,
                         p_CcTree->numOfEntries,
                         UINT_TO_PTR(p_CcTree->ccTreeBaseAddr), validate, 0,
                         h_FmTree, FALSE);
}