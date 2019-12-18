#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {scalar_t__ h_FmPcdCcSavedManipParams; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 

t_Handle FmPcdCcTreeGetSavedManipParams(t_Handle h_FmTree)
{
    t_FmPcdCcTree *p_FmPcdCcTree = (t_FmPcdCcTree *)h_FmTree;

    ASSERT_COND(p_FmPcdCcTree);

    return p_FmPcdCcTree->h_FmPcdCcSavedManipParams;
}