#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FmPcdManipInitUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdManipModifyUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

t_Error FmPcdManipUpdate(t_Handle h_FmPcd, t_Handle h_PcdParams,
                         t_Handle h_FmPort, t_Handle h_Manip, t_Handle h_Ad,
                         bool validate, int level, t_Handle h_FmTree,
                         bool modify)
{
    t_Error err;

    if (!modify)
        err = FmPcdManipInitUpdate(h_FmPcd, h_PcdParams, h_FmPort, h_Manip,
                                   h_Ad, validate, level, h_FmTree);
    else
        err = FmPcdManipModifyUpdate(h_Manip, h_Ad, validate, level, h_FmTree);

    return err;
}