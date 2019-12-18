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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct rndis_status_msg {int rm_status; int rm_stbuflen; int /*<<< orphan*/  rm_stbufoffset; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; } ;
typedef  int /*<<< orphan*/  change ;

/* Variables and functions */
#define  RNDIS_STATUS_LINK_SPEED_CHANGE 132 
#define  RNDIS_STATUS_MEDIA_CONNECT 131 
#define  RNDIS_STATUS_MEDIA_DISCONNECT 130 
#define  RNDIS_STATUS_NETWORK_CHANGE 129 
#define  RNDIS_STATUS_TASK_OFFLOAD_CURRENT_CONFIG 128 
 int RNDIS_STBUFOFFSET_ABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_change_network (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_update_link_status (struct hn_softc*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void 
hn_rndis_rx_status(struct hn_softc *sc, const void *data, int dlen)
{
	const struct rndis_status_msg *msg;
	int ofs;

	if (dlen < sizeof(*msg)) {
		if_printf(sc->hn_ifp, "invalid RNDIS status\n");
		return;
	}
	msg = data;

	switch (msg->rm_status) {
	case RNDIS_STATUS_MEDIA_CONNECT:
	case RNDIS_STATUS_MEDIA_DISCONNECT:
		hn_update_link_status(sc);
		break;

	case RNDIS_STATUS_TASK_OFFLOAD_CURRENT_CONFIG:
	case RNDIS_STATUS_LINK_SPEED_CHANGE:
		/* Not really useful; ignore. */
		break;

	case RNDIS_STATUS_NETWORK_CHANGE:
		ofs = RNDIS_STBUFOFFSET_ABS(msg->rm_stbufoffset);
		if (dlen < ofs + msg->rm_stbuflen ||
		    msg->rm_stbuflen < sizeof(uint32_t)) {
			if_printf(sc->hn_ifp, "network changed\n");
		} else {
			uint32_t change;

			memcpy(&change, ((const uint8_t *)msg) + ofs,
			    sizeof(change));
			if_printf(sc->hn_ifp, "network changed, change %u\n",
			    change);
		}
		hn_change_network(sc);
		break;

	default:
		if_printf(sc->hn_ifp, "unknown RNDIS status 0x%08x\n",
		    msg->rm_status);
		break;
	}
}