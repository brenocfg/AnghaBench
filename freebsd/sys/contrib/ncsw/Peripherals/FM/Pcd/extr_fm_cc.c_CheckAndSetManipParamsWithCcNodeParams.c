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
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_7__ {int numOfKeys; TYPE_2__* keyAndNextEngineParams; } ;
typedef  TYPE_3__ t_FmPcdCcNode ;
typedef  scalar_t__ t_Error ;
struct TYPE_5__ {scalar_t__ h_Manip; } ;
struct TYPE_6__ {TYPE_1__ nextEngineParams; } ;

/* Variables and functions */
 scalar_t__ E_OK ; 
 scalar_t__ FmPcdManipCheckParamsWithCcNodeParams (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error CheckAndSetManipParamsWithCcNodeParams(t_FmPcdCcNode *p_CcNode)
{
    t_Error err = E_OK;
    int i = 0;

    for (i = 0; i < p_CcNode->numOfKeys; i++)
    {
        if (p_CcNode->keyAndNextEngineParams[i].nextEngineParams.h_Manip)
        {
            err =
                    FmPcdManipCheckParamsWithCcNodeParams(
                            p_CcNode->keyAndNextEngineParams[i].nextEngineParams.h_Manip,
                            (t_Handle)p_CcNode);
            if (err)
                return err;
        }
    }

    return err;
}