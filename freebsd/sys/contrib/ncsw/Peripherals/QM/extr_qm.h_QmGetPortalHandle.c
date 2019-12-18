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
struct TYPE_3__ {scalar_t__* h_Portals; } ;
typedef  TYPE_1__ t_Qm ;
typedef  scalar_t__ t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 size_t CORE_GetId () ; 

__attribute__((used)) static __inline__ t_Handle QmGetPortalHandle(t_Handle h_Qm)
{
    t_Qm        *p_Qm       = (t_Qm*)h_Qm;

    ASSERT_COND(p_Qm);
    return p_Qm->h_Portals[CORE_GetId()];
}