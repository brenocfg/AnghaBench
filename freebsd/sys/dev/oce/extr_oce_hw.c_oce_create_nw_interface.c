#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  promisc; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  if_cap_flags; int /*<<< orphan*/  nifs; int /*<<< orphan*/  if_id; TYPE_1__ macaddr; scalar_t__ enable_hwlro; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_SH (TYPE_2__*) ; 
 scalar_t__ IS_XE201 (TYPE_2__*) ; 
 int /*<<< orphan*/  MBX_RX_IFACE_FLAGS_LRO ; 
 int /*<<< orphan*/  MBX_RX_IFACE_FLAGS_MULTICAST ; 
 int /*<<< orphan*/  MBX_RX_IFACE_FLAGS_PASS_L3L4_ERR ; 
 int /*<<< orphan*/  MBX_RX_IFACE_FLAGS_RSS ; 
 int /*<<< orphan*/  OCE_CAPAB_ENABLE ; 
 int /*<<< orphan*/  OCE_CAPAB_FLAGS ; 
 int /*<<< orphan*/  atomic_inc_32 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_rss_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  oce_delete_nw_interface (TYPE_2__*) ; 
 int oce_if_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int oce_rxf_set_promiscuous (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int oce_set_flow_control (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
oce_create_nw_interface(POCE_SOFTC sc)
{
	int rc;
	uint32_t capab_flags;
	uint32_t capab_en_flags;

	/* interface capabilities to give device when creating interface */
	capab_flags = OCE_CAPAB_FLAGS;

	/* capabilities to enable by default (others set dynamically) */
	capab_en_flags = OCE_CAPAB_ENABLE;

	if (IS_XE201(sc)) {
		/* LANCER A0 workaround */
		capab_en_flags &= ~MBX_RX_IFACE_FLAGS_PASS_L3L4_ERR;
		capab_flags &= ~MBX_RX_IFACE_FLAGS_PASS_L3L4_ERR;
	}

	if (IS_SH(sc) || IS_XE201(sc))
		capab_flags |= MBX_RX_IFACE_FLAGS_MULTICAST;

        if (sc->enable_hwlro) {
                capab_flags |= MBX_RX_IFACE_FLAGS_LRO;
                capab_en_flags |= MBX_RX_IFACE_FLAGS_LRO;
        }

	/* enable capabilities controlled via driver startup parameters */
	if (is_rss_enabled(sc))
		capab_en_flags |= MBX_RX_IFACE_FLAGS_RSS;
	else {
		capab_en_flags &= ~MBX_RX_IFACE_FLAGS_RSS;
		capab_flags &= ~MBX_RX_IFACE_FLAGS_RSS;
	}

	rc = oce_if_create(sc,
			   capab_flags,
			   capab_en_flags,
			   0, &sc->macaddr.mac_addr[0], &sc->if_id);
	if (rc)
		return rc;

	atomic_inc_32(&sc->nifs);

	sc->if_cap_flags = capab_en_flags;

	/* set default flow control */
	rc = oce_set_flow_control(sc, sc->flow_control);
	if (rc)
		goto error;

	rc = oce_rxf_set_promiscuous(sc, sc->promisc);
	if (rc)
		goto error;

	return rc;

error:
	oce_delete_nw_interface(sc);
	return rc;

}