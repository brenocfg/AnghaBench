#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {int /*<<< orphan*/  minorRev; int /*<<< orphan*/  majorRev; } ;
typedef  TYPE_3__ t_FmRevisionInfo ;
struct TYPE_9__ {TYPE_2__* p_FmStateStruct; } ;
typedef  TYPE_4__ t_Fm ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_6__ {int /*<<< orphan*/  minorRev; int /*<<< orphan*/  majorRev; } ;
struct TYPE_7__ {TYPE_1__ revInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 

t_Error FM_GetRevision(t_Handle h_Fm, t_FmRevisionInfo *p_FmRevisionInfo)
{
    t_Fm *p_Fm = (t_Fm*)h_Fm;

    p_FmRevisionInfo->majorRev = p_Fm->p_FmStateStruct->revInfo.majorRev;
    p_FmRevisionInfo->minorRev = p_Fm->p_FmStateStruct->revInfo.minorRev;

    return E_OK;
}