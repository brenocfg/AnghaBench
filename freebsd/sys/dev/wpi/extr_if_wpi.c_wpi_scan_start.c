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
struct wpi_softc {int dummy; } ;
struct ieee80211com {struct wpi_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_LED_LINK ; 
 int /*<<< orphan*/  wpi_set_led (struct wpi_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
wpi_scan_start(struct ieee80211com *ic)
{
	struct wpi_softc *sc = ic->ic_softc;

	wpi_set_led(sc, WPI_LED_LINK, 20, 2);
}