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
struct TYPE_3__ {scalar_t__ h_HcPortDev; scalar_t__* p_Frm; } ;
typedef  TYPE_1__ t_FmHc ;

/* Variables and functions */
 int /*<<< orphan*/  FM_PORT_Free (scalar_t__) ; 
 int HC_CMD_POOL_SIZE ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_FreeSmart (scalar_t__) ; 

void FmHcFree(t_Handle h_FmHc)
{
    t_FmHc  *p_FmHc = (t_FmHc*)h_FmHc;
    int     i;

    if (!p_FmHc)
        return;

    for (i=0; i<HC_CMD_POOL_SIZE; i++)
        if (p_FmHc->p_Frm[i])
            XX_FreeSmart(p_FmHc->p_Frm[i]);
        else
            break;

    if (p_FmHc->h_HcPortDev)
        FM_PORT_Free(p_FmHc->h_HcPortDev);

    XX_Free(p_FmHc);
}