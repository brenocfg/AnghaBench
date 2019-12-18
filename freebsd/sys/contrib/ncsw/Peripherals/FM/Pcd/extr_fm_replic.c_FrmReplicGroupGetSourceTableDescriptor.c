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
struct TYPE_3__ {void* p_SourceTd; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroup ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 

void * FrmReplicGroupGetSourceTableDescriptor(t_Handle h_ReplicGroup)
{
    t_FmPcdFrmReplicGroup   *p_ReplicGroup = (t_FmPcdFrmReplicGroup *)h_ReplicGroup;
    ASSERT_COND(p_ReplicGroup);

    return (p_ReplicGroup->p_SourceTd);
}