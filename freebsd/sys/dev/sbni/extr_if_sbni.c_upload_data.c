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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_int ;
struct sbni_softc {scalar_t__ wait_frameno; scalar_t__ inppos; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 scalar_t__ ETHER_MAX_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int append_frame_to_pkt (struct sbni_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int skip_tail (struct sbni_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upload_data(struct sbni_softc *sc, u_int framelen, u_int frameno,
	    u_int is_first, u_int32_t crc)
{
	int frame_ok;

	if (is_first) {
		sc->wait_frameno = frameno;
		sc->inppos = 0;
	}

	if (sc->wait_frameno == frameno) {

		if (sc->inppos + framelen  <=  ETHER_MAX_LEN) {
			frame_ok = append_frame_to_pkt(sc, framelen, crc);

		/*
		 * if CRC is right but framelen incorrect then transmitter
		 * error was occurred... drop entire packet
		 */
		} else if ((frame_ok = skip_tail(sc, framelen, crc)) != 0) {
			sc->wait_frameno = 0;
			sc->inppos = 0;
			if_inc_counter(sc->ifp, IFCOUNTER_IERRORS, 1);
			/* now skip all frames until is_first != 0 */
		}
	} else
		frame_ok = skip_tail(sc, framelen, crc);

	if (is_first && !frame_ok) {
		/*
		 * Frame has been violated, but we have stored
		 * is_first already... Drop entire packet.
		 */
		sc->wait_frameno = 0;
		if_inc_counter(sc->ifp, IFCOUNTER_IERRORS, 1);
	}

	return (frame_ok);
}