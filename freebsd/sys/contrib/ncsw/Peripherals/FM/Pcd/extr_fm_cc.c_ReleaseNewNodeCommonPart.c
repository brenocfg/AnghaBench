#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p_KeysMatchTableNew; scalar_t__ h_CurrentNode; scalar_t__ p_AdTableNew; } ;
typedef  TYPE_1__ t_FmPcdModifyCcKeyAdditionalParams ;
struct TYPE_5__ {int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_2__ t_FmPcdCcNode ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReleaseNewNodeCommonPart(
        t_FmPcdModifyCcKeyAdditionalParams *p_AdditionalInfo)
{
    if (p_AdditionalInfo->p_AdTableNew)
        FM_MURAM_FreeMem(
                FmPcdGetMuramHandle(
                        ((t_FmPcdCcNode *)(p_AdditionalInfo->h_CurrentNode))->h_FmPcd),
                p_AdditionalInfo->p_AdTableNew);

    if (p_AdditionalInfo->p_KeysMatchTableNew)
        FM_MURAM_FreeMem(
                FmPcdGetMuramHandle(
                        ((t_FmPcdCcNode *)(p_AdditionalInfo->h_CurrentNode))->h_FmPcd),
                p_AdditionalInfo->p_KeysMatchTableNew);
}