#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {scalar_t__* cgsHandles; TYPE_2__* cgrs; } ;
typedef  TYPE_3__ t_QmPortal ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {int* __state; } ;
struct TYPE_5__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error QmPortalRegisterCg(t_Handle h_QmPortal, t_Handle h_QmCg, uint8_t  cgId)
{
    t_QmPortal  *p_QmPortal = (t_QmPortal *)h_QmPortal;

    /* cgrs[0] is the mask of registered CG's*/
    if(p_QmPortal->cgrs[0].q.__state[cgId/32] & (0x80000000 >> (cgId % 32)))
        RETURN_ERROR(MINOR, E_BUSY, ("CG already used"));

    p_QmPortal->cgrs[0].q.__state[cgId/32] |=  0x80000000 >> (cgId % 32);
    p_QmPortal->cgsHandles[cgId] = h_QmCg;

    return E_OK;
}