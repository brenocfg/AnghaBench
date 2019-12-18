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
struct ecore_vlan_mac_obj {int dummy; } ;
struct bxe_softc {TYPE_1__* sp_objs; int /*<<< orphan*/  ifp; } ;
struct bxe_set_addr_ctx {scalar_t__ rc; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; struct bxe_softc* member_0; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_2__ {struct ecore_vlan_mac_obj mac_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ECORE_UC_LIST_MAC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bxe_del_all_macs (struct bxe_softc*,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_set_addr ; 
 int bxe_set_mac_one (struct bxe_softc*,int /*<<< orphan*/ *,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_foreach_lladdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bxe_set_addr_ctx*) ; 

__attribute__((used)) static int
bxe_set_uc_list(struct bxe_softc *sc)
{
    if_t ifp = sc->ifp;
    struct ecore_vlan_mac_obj *mac_obj = &sc->sp_objs->mac_obj;
    struct bxe_set_addr_ctx ctx = { sc, 0, 0 };
    int rc;

    /* first schedule a cleanup up of old configuration */
    rc = bxe_del_all_macs(sc, mac_obj, ECORE_UC_LIST_MAC, FALSE);
    if (rc < 0) {
        BLOGE(sc, "Failed to schedule delete of all ETH MACs (%d)\n", rc);
        return (rc);
    }

    if_foreach_lladdr(ifp, bxe_set_addr, &ctx);
    if (ctx.rc < 0)
	return (ctx.rc);

    /* Execute the pending commands */
    bit_set(&ctx.ramrod_flags, RAMROD_CONT);
    return (bxe_set_mac_one(sc, NULL, mac_obj, FALSE /* don't care */,
                            ECORE_UC_LIST_MAC, &ctx.ramrod_flags));
}