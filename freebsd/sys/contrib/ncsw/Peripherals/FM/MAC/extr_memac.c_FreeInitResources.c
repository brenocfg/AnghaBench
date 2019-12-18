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
struct TYPE_5__ {int /*<<< orphan*/ * p_UnicastAddrHash; int /*<<< orphan*/ * p_MulticastAddrHash; int /*<<< orphan*/  macId; TYPE_1__ fmMacControllerDriver; int /*<<< orphan*/  enetMode; } ;
typedef  TYPE_2__ t_Memac ;
typedef  scalar_t__ e_FmMacType ;

/* Variables and functions */
 scalar_t__ ENET_SPEED_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeHashTable (int /*<<< orphan*/ *) ; 
 scalar_t__ e_ENET_SPEED_10000 ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 scalar_t__ e_FM_MAC_10G ; 
 scalar_t__ e_FM_MAC_1G ; 
 int /*<<< orphan*/  e_FM_MOD_10G_MAC ; 
 int /*<<< orphan*/  e_FM_MOD_1G_MAC ; 

__attribute__((used)) static void FreeInitResources(t_Memac *p_Memac)
{
    e_FmMacType portType;

    portType =
        ((ENET_SPEED_FROM_MODE(p_Memac->enetMode) < e_ENET_SPEED_10000) ? e_FM_MAC_1G : e_FM_MAC_10G);

    if (portType == e_FM_MAC_10G)
        FmUnregisterIntr(p_Memac->fmMacControllerDriver.h_Fm, e_FM_MOD_10G_MAC, p_Memac->macId, e_FM_INTR_TYPE_ERR);
    else
        FmUnregisterIntr(p_Memac->fmMacControllerDriver.h_Fm, e_FM_MOD_1G_MAC, p_Memac->macId, e_FM_INTR_TYPE_ERR);

    /* release the driver's group hash table */
    FreeHashTable(p_Memac->p_MulticastAddrHash);
    p_Memac->p_MulticastAddrHash =   NULL;

    /* release the driver's individual hash table */
    FreeHashTable(p_Memac->p_UnicastAddrHash);
    p_Memac->p_UnicastAddrHash =     NULL;
}