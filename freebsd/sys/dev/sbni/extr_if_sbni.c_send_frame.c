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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  all_tx_number; int /*<<< orphan*/  resend_tx_number; } ;
struct sbni_softc {int state; scalar_t__ framelen; scalar_t__ tx_frameno; TYPE_1__ in_stats; scalar_t__ trans_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32_INITIAL ; 
 int /*<<< orphan*/  CSR0 ; 
 int FL_NEED_RESEND ; 
 int FL_WAIT_ACK ; 
 scalar_t__ TR_ERROR_COUNT ; 
 int TR_REQ ; 
 int /*<<< orphan*/  download_data (struct sbni_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_xmit_queue (struct sbni_softc*) ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbni_outsb (struct sbni_softc*,int*,int) ; 
 int /*<<< orphan*/  send_frame_header (struct sbni_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
send_frame(struct sbni_softc *sc)
{
	u_int32_t crc;
	u_char csr0;

	crc = CRC32_INITIAL;
	if (sc->state & FL_NEED_RESEND) {

		/* if frame was sended but not ACK'ed - resend it */
		if (sc->trans_errors) {
			sc->trans_errors--;
			if (sc->framelen != 0)
				sc->in_stats.resend_tx_number++;
		} else {
			/* cannot xmit with many attempts */
			drop_xmit_queue(sc);
			goto do_send;
		}
	} else
		sc->trans_errors = TR_ERROR_COUNT;

	send_frame_header(sc, &crc);
	sc->state |= FL_NEED_RESEND;
	/*
	 * FL_NEED_RESEND will be cleared after ACK, but if empty
	 * frame sended then in prepare_to_send next frame
	 */


	if (sc->framelen) {
		download_data(sc, &crc);
		sc->in_stats.all_tx_number++;
		sc->state |= FL_WAIT_ACK;
	}

	sbni_outsb(sc, (u_char *)&crc, sizeof crc);

do_send:
	csr0 = sbni_inb(sc, CSR0);
	sbni_outb(sc, CSR0, csr0 & ~TR_REQ);

	if (sc->tx_frameno) {
		/* next frame exists - request to send */
		sbni_outb(sc, CSR0, csr0 | TR_REQ);
	}
}