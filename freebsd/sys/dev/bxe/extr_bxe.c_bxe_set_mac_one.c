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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  mac; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  vlan_mac_flags; TYPE_2__ u; } ;
struct ecore_vlan_mac_ramrod_params {unsigned long ramrod_flags; TYPE_3__ user_req; struct ecore_vlan_mac_obj* vlan_mac_obj; } ;
struct ecore_vlan_mac_obj {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ramrod_param ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,char*,int) ; 
 int /*<<< orphan*/  DBG_SP ; 
 int ECORE_EXISTS ; 
 int /*<<< orphan*/  ECORE_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  ECORE_VLAN_MAC_DEL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  bxe_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int ecore_config_vlan_mac (struct bxe_softc*,struct ecore_vlan_mac_ramrod_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ecore_vlan_mac_ramrod_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_set_mac_one(struct bxe_softc          *sc,
                uint8_t                   *mac,
                struct ecore_vlan_mac_obj *obj,
                uint8_t                   set,
                int                       mac_type,
                unsigned long             *ramrod_flags)
{
    struct ecore_vlan_mac_ramrod_params ramrod_param;
    int rc;

    memset(&ramrod_param, 0, sizeof(ramrod_param));

    /* fill in general parameters */
    ramrod_param.vlan_mac_obj = obj;
    ramrod_param.ramrod_flags = *ramrod_flags;

    /* fill a user request section if needed */
    if (!bxe_test_bit(RAMROD_CONT, ramrod_flags)) {
        memcpy(ramrod_param.user_req.u.mac.mac, mac, ETH_ALEN);

        bxe_set_bit(mac_type, &ramrod_param.user_req.vlan_mac_flags);

        /* Set the command: ADD or DEL */
        ramrod_param.user_req.cmd = (set) ? ECORE_VLAN_MAC_ADD :
                                            ECORE_VLAN_MAC_DEL;
    }

    rc = ecore_config_vlan_mac(sc, &ramrod_param);

    if (rc == ECORE_EXISTS) {
        BLOGD(sc, DBG_SP, "Failed to schedule ADD operations (EEXIST)\n");
        /* do not treat adding same MAC as error */
        rc = 0;
    } else if (rc < 0) {
        BLOGE(sc, "%s MAC failed (%d)\n", (set ? "Set" : "Delete"), rc);
    }

    return (rc);
}