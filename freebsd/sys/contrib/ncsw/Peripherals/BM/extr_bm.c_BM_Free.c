#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {scalar_t__ guestId; scalar_t__ errIrq; struct TYPE_4__* p_BmDriverParams; int /*<<< orphan*/  moduleName; } ;
typedef  TYPE_1__ t_Bm ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FreeInitResources (TYPE_1__*) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  XX_DisableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_FreeIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_IpcUnregisterMsgHandler (int /*<<< orphan*/ ) ; 

t_Error BM_Free(t_Handle h_Bm)
{
    t_Bm    *p_Bm = (t_Bm *)h_Bm;

    if (!p_Bm)
       return ERROR_CODE(E_INVALID_HANDLE);

    if (p_Bm->guestId == NCSW_MASTER_ID)
    {
        XX_IpcUnregisterMsgHandler(p_Bm->moduleName);
        if (p_Bm->errIrq  != NO_IRQ)
        {
            XX_DisableIntr(p_Bm->errIrq);
            XX_FreeIntr(p_Bm->errIrq);
        }
    }
    FreeInitResources(p_Bm);

    if(p_Bm->p_BmDriverParams)
        XX_Free(p_Bm->p_BmDriverParams);

    XX_Free(p_Bm);
    return E_OK;
}