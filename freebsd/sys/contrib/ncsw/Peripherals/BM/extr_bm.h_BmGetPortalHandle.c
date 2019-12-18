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
struct TYPE_3__ {scalar_t__* h_Portals; } ;
typedef  TYPE_1__ t_Bm ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 size_t CORE_GetId () ; 

__attribute__((used)) static __inline__ t_Handle BmGetPortalHandle(t_Handle h_Bm)
{
    t_Bm *p_Bm = (t_Bm*)h_Bm;
    ASSERT_COND(p_Bm);
    return p_Bm->h_Portals[CORE_GetId()];
}