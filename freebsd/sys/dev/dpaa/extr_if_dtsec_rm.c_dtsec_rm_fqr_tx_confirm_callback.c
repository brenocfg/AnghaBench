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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  struct dtsec_softc* t_Handle ;
typedef  int /*<<< orphan*/  t_DpaaSGTE ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
struct dtsec_softc {scalar_t__ sc_tx_fqr_full; int /*<<< orphan*/  sc_tx_conf_fqr; int /*<<< orphan*/  sc_dev; } ;
struct dtsec_rm_frame_info {int /*<<< orphan*/  fi_mbuf; } ;
typedef  int /*<<< orphan*/  e_RxStoreResponse ;

/* Variables and functions */
 int /*<<< orphan*/ * DPAA_FD_GET_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ DPAA_FD_GET_STATUS (int /*<<< orphan*/ *) ; 
 struct dtsec_rm_frame_info* DPAA_SGTE_GET_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dtsec_rm_fi_free (struct dtsec_softc*,struct dtsec_rm_frame_info*) ; 
 int /*<<< orphan*/  dtsec_rm_if_start_locked (struct dtsec_softc*) ; 
 int /*<<< orphan*/  e_QM_FQR_COUNTERS_FRAME ; 
 int /*<<< orphan*/  e_RX_STORE_RESPONSE_CONTINUE ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 unsigned int qman_fqr_get_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static e_RxStoreResponse
dtsec_rm_fqr_tx_confirm_callback(t_Handle app, t_Handle fqr, t_Handle portal,
    uint32_t fqid_off, t_DpaaFD *frame)
{
	struct dtsec_rm_frame_info *fi;
	struct dtsec_softc *sc;
	unsigned int qlen;
	t_DpaaSGTE *sgt0;

	sc = app;

	if (DPAA_FD_GET_STATUS(frame) != 0)
		device_printf(sc->sc_dev, "TX error: 0x%08X\n",
		    DPAA_FD_GET_STATUS(frame));

	/*
	 * We are storing struct dtsec_rm_frame_info in first entry
	 * of scatter-gather table.
	 */
	sgt0 = DPAA_FD_GET_ADDR(frame);
	fi = DPAA_SGTE_GET_ADDR(sgt0);

	/* Free transmitted frame */
	m_freem(fi->fi_mbuf);
	dtsec_rm_fi_free(sc, fi);

	qlen = qman_fqr_get_counter(sc->sc_tx_conf_fqr, 0,
	    e_QM_FQR_COUNTERS_FRAME);

	if (qlen == 0) {
		DTSEC_LOCK(sc);

		if (sc->sc_tx_fqr_full) {
			sc->sc_tx_fqr_full = 0;
			dtsec_rm_if_start_locked(sc);
		}

		DTSEC_UNLOCK(sc);
	}

	return (e_RX_STORE_RESPONSE_CONTINUE);
}