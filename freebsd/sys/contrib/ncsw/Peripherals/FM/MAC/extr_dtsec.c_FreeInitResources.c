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
typedef  TYPE_2__ t_Dtsec ;

/* Variables and functions */
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeHashTable (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  XX_DisableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_FreeIntr (scalar_t__) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_1G_MAC ; 

__attribute__((used)) static void FreeInitResources(t_Dtsec *p_Dtsec)
{
    if (p_Dtsec->mdioIrq != NO_IRQ)
    {
        XX_DisableIntr(p_Dtsec->mdioIrq);
        XX_FreeIntr(p_Dtsec->mdioIrq);
    }
    FmUnregisterIntr(p_Dtsec->fmMacControllerDriver.h_Fm, e_FM_MOD_1G_MAC, p_Dtsec->macId, e_FM_INTR_TYPE_ERR);
    FmUnregisterIntr(p_Dtsec->fmMacControllerDriver.h_Fm, e_FM_MOD_1G_MAC, p_Dtsec->macId, e_FM_INTR_TYPE_NORMAL);

    /* release the driver's group hash table */
    FreeHashTable(p_Dtsec->p_MulticastAddrHash);
    p_Dtsec->p_MulticastAddrHash =   NULL;

    /* release the driver's individual hash table */
    FreeHashTable(p_Dtsec->p_UnicastAddrHash);
    p_Dtsec->p_UnicastAddrHash =     NULL;
}