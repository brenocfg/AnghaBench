#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rndis_msghdr {int rm_type; } ;
struct rndis_comp_hdr {int /*<<< orphan*/  rm_rid; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_xact; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_RNDIS_RID_COMPAT_MAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  REMOTE_NDIS_INITIALIZE_CMPLT 132 
#define  REMOTE_NDIS_KEEPALIVE_CMPLT 131 
#define  REMOTE_NDIS_QUERY_CMPLT 130 
#define  REMOTE_NDIS_RESET_CMPLT 129 
#define  REMOTE_NDIS_SET_CMPLT 128 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_wakeup (int /*<<< orphan*/ ,struct rndis_comp_hdr const*,int) ; 

void
hn_rndis_rx_ctrl(struct hn_softc *sc, const void *data, int dlen)
{
	const struct rndis_comp_hdr *comp;
	const struct rndis_msghdr *hdr;

	KASSERT(dlen >= sizeof(*hdr), ("invalid RNDIS msg\n"));
	hdr = data;

	switch (hdr->rm_type) {
	case REMOTE_NDIS_INITIALIZE_CMPLT:
	case REMOTE_NDIS_QUERY_CMPLT:
	case REMOTE_NDIS_SET_CMPLT:
	case REMOTE_NDIS_KEEPALIVE_CMPLT:	/* unused */
		if (dlen < sizeof(*comp)) {
			if_printf(sc->hn_ifp, "invalid RNDIS cmplt\n");
			return;
		}
		comp = data;

		KASSERT(comp->rm_rid > HN_RNDIS_RID_COMPAT_MAX,
		    ("invalid RNDIS rid 0x%08x\n", comp->rm_rid));
		vmbus_xact_ctx_wakeup(sc->hn_xact, comp, dlen);
		break;

	case REMOTE_NDIS_RESET_CMPLT:
		/*
		 * Reset completed, no rid.
		 *
		 * NOTE:
		 * RESET is not issued by hn(4), so this message should
		 * _not_ be observed.
		 */
		if_printf(sc->hn_ifp, "RESET cmplt received\n");
		break;

	default:
		if_printf(sc->hn_ifp, "unknown RNDIS msg 0x%x\n",
		    hdr->rm_type);
		break;
	}
}