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
typedef  int uint32_t ;
struct ipw_status {int /*<<< orphan*/  code; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; } ;
struct ipw_softc {int flags; int rxcur; int /*<<< orphan*/  rbd_map; int /*<<< orphan*/  rbd_dmat; int /*<<< orphan*/  sc_dev; struct ipw_soft_bd* srbd_list; struct ipw_status* status_list; int /*<<< orphan*/  status_map; int /*<<< orphan*/  status_dmat; } ;
struct ipw_soft_buf {int dummy; } ;
struct ipw_soft_bd {TYPE_1__* bd; struct ipw_soft_buf* priv; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CSR_READ_4 (struct ipw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  IPW_CSR_RX_READ ; 
 int /*<<< orphan*/  IPW_CSR_RX_WRITE ; 
 int IPW_FLAG_FW_INITED ; 
 int IPW_NRBD ; 
#define  IPW_STATUS_CODE_COMMAND 132 
#define  IPW_STATUS_CODE_DATA_802_11 131 
#define  IPW_STATUS_CODE_DATA_802_3 130 
#define  IPW_STATUS_CODE_NEWSTATE 129 
#define  IPW_STATUS_CODE_NOTIFICATION 128 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipw_rx_cmd_intr (struct ipw_softc*,struct ipw_soft_buf*) ; 
 int /*<<< orphan*/  ipw_rx_data_intr (struct ipw_softc*,struct ipw_status*,struct ipw_soft_bd*,struct ipw_soft_buf*) ; 
 int /*<<< orphan*/  ipw_rx_newstate_intr (struct ipw_softc*,struct ipw_soft_buf*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipw_rx_intr(struct ipw_softc *sc)
{
	struct ipw_status *status;
	struct ipw_soft_bd *sbd;
	struct ipw_soft_buf *sbuf;
	uint32_t r, i;

	if (!(sc->flags & IPW_FLAG_FW_INITED))
		return;

	r = CSR_READ_4(sc, IPW_CSR_RX_READ);

	bus_dmamap_sync(sc->status_dmat, sc->status_map, BUS_DMASYNC_POSTREAD);

	for (i = (sc->rxcur + 1) % IPW_NRBD; i != r; i = (i + 1) % IPW_NRBD) {
		status = &sc->status_list[i];
		sbd = &sc->srbd_list[i];
		sbuf = sbd->priv;

		switch (le16toh(status->code) & 0xf) {
		case IPW_STATUS_CODE_COMMAND:
			ipw_rx_cmd_intr(sc, sbuf);
			break;

		case IPW_STATUS_CODE_NEWSTATE:
			ipw_rx_newstate_intr(sc, sbuf);
			break;

		case IPW_STATUS_CODE_DATA_802_3:
		case IPW_STATUS_CODE_DATA_802_11:
			ipw_rx_data_intr(sc, status, sbd, sbuf);
			break;

		case IPW_STATUS_CODE_NOTIFICATION:
			DPRINTFN(2, ("notification status, len %u flags 0x%x\n",
			    le32toh(status->len), status->flags));
			/* XXX maybe drive state machine AUTH->ASSOC? */
			break;

		default:
			device_printf(sc->sc_dev, "unexpected status code %u\n",
			    le16toh(status->code));
		}

		/* firmware was killed, stop processing received frames */
		if (!(sc->flags & IPW_FLAG_FW_INITED))
			return;

		sbd->bd->flags = 0;
	}

	bus_dmamap_sync(sc->rbd_dmat, sc->rbd_map, BUS_DMASYNC_PREWRITE);

	/* kick the firmware */
	sc->rxcur = (r == 0) ? IPW_NRBD - 1 : r - 1;
	CSR_WRITE_4(sc, IPW_CSR_RX_WRITE, sc->rxcur);
}