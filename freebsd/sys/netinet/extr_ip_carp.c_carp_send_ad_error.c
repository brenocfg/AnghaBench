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
struct carp_softc {scalar_t__ sc_sendad_errors; scalar_t__ sc_sendad_success; TYPE_1__* sc_carpdev; } ;
typedef  int /*<<< orphan*/  fmt ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 scalar_t__ CARP_SENDAD_MAX_ERRORS ; 
 scalar_t__ CARP_SENDAD_MIN_SUCCESS ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  V_carp_senderr_adj ; 
 int /*<<< orphan*/  carp_demote_adj (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int,...) ; 

__attribute__((used)) static void
carp_send_ad_error(struct carp_softc *sc, int error)
{

	if (error) {
		if (sc->sc_sendad_errors < INT_MAX)
			sc->sc_sendad_errors++;
		if (sc->sc_sendad_errors == CARP_SENDAD_MAX_ERRORS) {
			static const char fmt[] = "send error %d on %s";
			char msg[sizeof(fmt) + IFNAMSIZ];

			sprintf(msg, fmt, error, sc->sc_carpdev->if_xname);
			carp_demote_adj(V_carp_senderr_adj, msg);
		}
		sc->sc_sendad_success = 0;
	} else {
		if (sc->sc_sendad_errors >= CARP_SENDAD_MAX_ERRORS &&
		    ++sc->sc_sendad_success >= CARP_SENDAD_MIN_SUCCESS) {
			static const char fmt[] = "send ok on %s";
			char msg[sizeof(fmt) + IFNAMSIZ];

			sprintf(msg, fmt, sc->sc_carpdev->if_xname);
			carp_demote_adj(-V_carp_senderr_adj, msg);
			sc->sc_sendad_errors = 0;
		} else
			sc->sc_sendad_errors = 0;
	}
}