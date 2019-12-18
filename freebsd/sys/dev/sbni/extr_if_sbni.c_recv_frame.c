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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  bad_rx_number; int /*<<< orphan*/  all_rx_number; } ;
struct sbni_softc {TYPE_1__ in_stats; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32_INITIAL ; 
 int /*<<< orphan*/  CSR0 ; 
 int CT_ZER ; 
 int /*<<< orphan*/  FL_PREV_OK ; 
 int /*<<< orphan*/  change_level (struct sbni_softc*) ; 
 scalar_t__ check_fhdr (struct sbni_softc*,int*,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interpret_ack (struct sbni_softc*,int) ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int) ; 
 int skip_tail (struct sbni_softc*,int,int /*<<< orphan*/ ) ; 
 int upload_data (struct sbni_softc*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
recv_frame(struct sbni_softc *sc)
{
	u_int32_t crc;
	u_int framelen, frameno, ack;
	u_int is_first, frame_ok;

	crc = CRC32_INITIAL;
	if (check_fhdr(sc, &framelen, &frameno, &ack, &is_first, &crc)) {
		frame_ok = framelen > 4 ?
		    upload_data(sc, framelen, frameno, is_first, crc) :
		    skip_tail(sc, framelen, crc);
		if (frame_ok)
			interpret_ack(sc, ack);
	} else {
		framelen = 0;
		frame_ok = 0;
	}

	sbni_outb(sc, CSR0, sbni_inb(sc, CSR0) ^ CT_ZER);
	if (frame_ok) {
		sc->state |= FL_PREV_OK;
		if (framelen > 4)
			sc->in_stats.all_rx_number++;
	} else {
		sc->state &= ~FL_PREV_OK;
		change_level(sc);
		sc->in_stats.all_rx_number++;
		sc->in_stats.bad_rx_number++;
	}

	return (!frame_ok || framelen > 4);
}