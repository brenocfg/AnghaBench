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
typedef  size_t uint8_t ;
struct ieee80211com {scalar_t__ ic_curmode; } ;
struct wpi_softc {int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct wpi_mrr_setup {void* which; TYPE_1__* rates; } ;
struct TYPE_2__ {size_t next; void* ntries; void* plcp; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  WPI_CMD_MRR_SETUP ; 
 int /*<<< orphan*/  WPI_MRR_CTL ; 
 int /*<<< orphan*/  WPI_MRR_DATA ; 
 void* WPI_NTRIES_DEFAULT ; 
 size_t WPI_RIDX_CCK1 ; 
 size_t WPI_RIDX_CCK11 ; 
 size_t WPI_RIDX_CCK2 ; 
 size_t WPI_RIDX_OFDM54 ; 
 size_t WPI_RIDX_OFDM6 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int wpi_cmd (struct wpi_softc*,int /*<<< orphan*/ ,struct wpi_mrr_setup*,int,int /*<<< orphan*/ ) ; 
 void** wpi_ridx_to_plcp ; 

__attribute__((used)) static int
wpi_mrr_setup(struct wpi_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct wpi_mrr_setup mrr;
	uint8_t i;
	int error;

	/* CCK rates (not used with 802.11a). */
	for (i = WPI_RIDX_CCK1; i <= WPI_RIDX_CCK11; i++) {
		mrr.rates[i].flags = 0;
		mrr.rates[i].plcp = wpi_ridx_to_plcp[i];
		/* Fallback to the immediate lower CCK rate (if any.) */
		mrr.rates[i].next =
		    (i == WPI_RIDX_CCK1) ? WPI_RIDX_CCK1 : i - 1;
		/* Try twice at this rate before falling back to "next". */
		mrr.rates[i].ntries = WPI_NTRIES_DEFAULT;
	}
	/* OFDM rates (not used with 802.11b). */
	for (i = WPI_RIDX_OFDM6; i <= WPI_RIDX_OFDM54; i++) {
		mrr.rates[i].flags = 0;
		mrr.rates[i].plcp = wpi_ridx_to_plcp[i];
		/* Fallback to the immediate lower rate (if any.) */
		/* We allow fallback from OFDM/6 to CCK/2 in 11b/g mode. */
		mrr.rates[i].next = (i == WPI_RIDX_OFDM6) ?
		    ((ic->ic_curmode == IEEE80211_MODE_11A) ?
			WPI_RIDX_OFDM6 : WPI_RIDX_CCK2) :
		    i - 1;
		/* Try twice at this rate before falling back to "next". */
		mrr.rates[i].ntries = WPI_NTRIES_DEFAULT;
	}
	/* Setup MRR for control frames. */
	mrr.which = htole32(WPI_MRR_CTL);
	error = wpi_cmd(sc, WPI_CMD_MRR_SETUP, &mrr, sizeof mrr, 0);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not setup MRR for control frames\n");
		return error;
	}
	/* Setup MRR for data frames. */
	mrr.which = htole32(WPI_MRR_DATA);
	error = wpi_cmd(sc, WPI_CMD_MRR_SETUP, &mrr, sizeof mrr, 0);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not setup MRR for data frames\n");
		return error;
	}
	return 0;
}