#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ti_event_ring_map; int /*<<< orphan*/  ti_event_ring_tag; } ;
struct TYPE_6__ {struct ti_event_desc* ti_event_ring; } ;
struct TYPE_5__ {size_t ti_idx; } ;
struct ti_softc {size_t ti_ev_saved_considx; TYPE_3__ ti_cdata; int /*<<< orphan*/  ti_dev; TYPE_4__* ti_ifp; int /*<<< orphan*/  ti_linkstat; TYPE_2__ ti_rdata; TYPE_1__ ti_ev_prodidx; } ;
struct ti_event_desc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  if_baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  IF_Gbps (unsigned long) ; 
 int /*<<< orphan*/  IF_Mbps (int) ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  TI_EVENT_CODE (struct ti_event_desc*) ; 
 int TI_EVENT_EVENT (struct ti_event_desc*) ; 
 int /*<<< orphan*/  TI_EVENT_RING_CNT ; 
 int /*<<< orphan*/  TI_EV_CODE_ERR_BADCFG ; 
 int /*<<< orphan*/  TI_EV_CODE_ERR_INVAL_CMD ; 
 int /*<<< orphan*/  TI_EV_CODE_ERR_UNIMP_CMD ; 
 int /*<<< orphan*/  TI_EV_CODE_GIG_LINK_UP ; 
 int /*<<< orphan*/  TI_EV_CODE_LINK_DOWN ; 
 int /*<<< orphan*/  TI_EV_CODE_LINK_UP ; 
#define  TI_EV_ERROR 133 
#define  TI_EV_FIRMWARE_UP 132 
#define  TI_EV_LINKSTAT_CHANGED 131 
#define  TI_EV_MCAST_UPDATED 130 
#define  TI_EV_RESET_JUMBO_RING 129 
#define  TI_EV_STATS_UPDATED 128 
 int /*<<< orphan*/  TI_GCR_EVENTCONS_IDX ; 
 int /*<<< orphan*/  TI_INC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_init2 (struct ti_softc*) ; 

__attribute__((used)) static void
ti_handle_events(struct ti_softc *sc)
{
	struct ti_event_desc *e;

	if (sc->ti_rdata.ti_event_ring == NULL)
		return;

	bus_dmamap_sync(sc->ti_cdata.ti_event_ring_tag,
	    sc->ti_cdata.ti_event_ring_map, BUS_DMASYNC_POSTREAD);
	while (sc->ti_ev_saved_considx != sc->ti_ev_prodidx.ti_idx) {
		e = &sc->ti_rdata.ti_event_ring[sc->ti_ev_saved_considx];
		switch (TI_EVENT_EVENT(e)) {
		case TI_EV_LINKSTAT_CHANGED:
			sc->ti_linkstat = TI_EVENT_CODE(e);
			if (sc->ti_linkstat == TI_EV_CODE_LINK_UP) {
				if_link_state_change(sc->ti_ifp, LINK_STATE_UP);
				sc->ti_ifp->if_baudrate = IF_Mbps(100);
				if (bootverbose)
					device_printf(sc->ti_dev,
					    "10/100 link up\n");
			} else if (sc->ti_linkstat == TI_EV_CODE_GIG_LINK_UP) {
				if_link_state_change(sc->ti_ifp, LINK_STATE_UP);
				sc->ti_ifp->if_baudrate = IF_Gbps(1UL);
				if (bootverbose)
					device_printf(sc->ti_dev,
					    "gigabit link up\n");
			} else if (sc->ti_linkstat == TI_EV_CODE_LINK_DOWN) {
				if_link_state_change(sc->ti_ifp,
				    LINK_STATE_DOWN);
				sc->ti_ifp->if_baudrate = 0;
				if (bootverbose)
					device_printf(sc->ti_dev,
					    "link down\n");
			}
			break;
		case TI_EV_ERROR:
			if (TI_EVENT_CODE(e) == TI_EV_CODE_ERR_INVAL_CMD)
				device_printf(sc->ti_dev, "invalid command\n");
			else if (TI_EVENT_CODE(e) == TI_EV_CODE_ERR_UNIMP_CMD)
				device_printf(sc->ti_dev, "unknown command\n");
			else if (TI_EVENT_CODE(e) == TI_EV_CODE_ERR_BADCFG)
				device_printf(sc->ti_dev, "bad config data\n");
			break;
		case TI_EV_FIRMWARE_UP:
			ti_init2(sc);
			break;
		case TI_EV_STATS_UPDATED:
		case TI_EV_RESET_JUMBO_RING:
		case TI_EV_MCAST_UPDATED:
			/* Who cares. */
			break;
		default:
			device_printf(sc->ti_dev, "unknown event: %d\n",
			    TI_EVENT_EVENT(e));
			break;
		}
		/* Advance the consumer index. */
		TI_INC(sc->ti_ev_saved_considx, TI_EVENT_RING_CNT);
		CSR_WRITE_4(sc, TI_GCR_EVENTCONS_IDX, sc->ti_ev_saved_considx);
	}
	bus_dmamap_sync(sc->ti_cdata.ti_event_ring_tag,
	    sc->ti_cdata.ti_event_ring_map, BUS_DMASYNC_PREREAD);
}