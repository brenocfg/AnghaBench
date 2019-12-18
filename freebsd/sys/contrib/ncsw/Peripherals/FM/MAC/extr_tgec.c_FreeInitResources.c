#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  h_Fm; } ;
struct TYPE_5__ {scalar_t__ mdioIrq; int /*<<< orphan*/ * p_UnicastAddrHash; int /*<<< orphan*/ * p_MulticastAddrHash; int /*<<< orphan*/  macId; TYPE_1__ fmMacControllerDriver; } ;
typedef  TYPE_2__ t_Tgec ;

/* Variables and functions */
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeHashTable (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  XX_DisableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_FreeIntr (scalar_t__) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_MOD_10G_MAC ; 

__attribute__((used)) static void FreeInitResources(t_Tgec *p_Tgec)
{
    if (p_Tgec->mdioIrq != NO_IRQ)
    {
        XX_DisableIntr(p_Tgec->mdioIrq);
        XX_FreeIntr(p_Tgec->mdioIrq);
    }

    FmUnregisterIntr(p_Tgec->fmMacControllerDriver.h_Fm, e_FM_MOD_10G_MAC, p_Tgec->macId, e_FM_INTR_TYPE_ERR);

    /* release the driver's group hash table */
    FreeHashTable(p_Tgec->p_MulticastAddrHash);
    p_Tgec->p_MulticastAddrHash =   NULL;

    /* release the driver's individual hash table */
    FreeHashTable(p_Tgec->p_UnicastAddrHash);
    p_Tgec->p_UnicastAddrHash =     NULL;
}