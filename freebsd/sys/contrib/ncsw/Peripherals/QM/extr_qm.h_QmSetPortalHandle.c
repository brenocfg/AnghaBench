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
struct TYPE_2__ {scalar_t__* h_Portals; } ;
typedef  TYPE_1__ t_Qm ;
typedef  scalar_t__ t_Handle ;
typedef  size_t e_DpaaSwPortal ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 

__attribute__((used)) static __inline__ void QmSetPortalHandle(t_Handle h_Qm, t_Handle h_Portal, e_DpaaSwPortal portalId)
{
    ASSERT_COND(!((t_Qm*)h_Qm)->h_Portals[portalId] || !h_Portal);
    ((t_Qm*)h_Qm)->h_Portals[portalId] = h_Portal;
}