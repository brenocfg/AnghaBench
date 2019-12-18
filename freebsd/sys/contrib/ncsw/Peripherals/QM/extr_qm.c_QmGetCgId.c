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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {size_t partCgsBase; size_t partNumOfCgs; scalar_t__* cgsUsed; } ;
typedef  TYPE_1__ t_Qm ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 

t_Error QmGetCgId(t_Handle h_Qm, uint8_t *p_CgId)
{
    t_Qm        *p_Qm = (t_Qm *)h_Qm;
    uint16_t    i;

    for(i = p_Qm->partCgsBase;i<p_Qm->partCgsBase+p_Qm->partNumOfCgs;i++)
        if (!p_Qm->cgsUsed[i])
        {
            p_Qm->cgsUsed[i] = (uint8_t)TRUE;
            *p_CgId = (uint8_t)i;
            break;
        }
    if(i == (p_Qm->partCgsBase+p_Qm->partNumOfCgs))
        RETURN_ERROR(MINOR, E_BUSY, ("No available CG"));
    else
        return E_OK;
}