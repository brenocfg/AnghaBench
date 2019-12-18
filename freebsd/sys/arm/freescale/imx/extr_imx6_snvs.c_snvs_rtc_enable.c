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
typedef  int uint32_t ;
struct snvs_softc {int lpcr; } ;

/* Variables and functions */
 int LPCR_SRTC_ENV ; 
 int RD4 (struct snvs_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNVS_LPCR ; 
 int /*<<< orphan*/  WR4 (struct snvs_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
snvs_rtc_enable(struct snvs_softc *sc, bool enable)
{
	uint32_t enbit;

	if (enable)
		sc->lpcr |= LPCR_SRTC_ENV;
	else
		sc->lpcr &= ~LPCR_SRTC_ENV;
	WR4(sc, SNVS_LPCR, sc->lpcr);

	/* Wait for the hardware to achieve the requested state. */
	enbit = sc->lpcr & LPCR_SRTC_ENV;
	while ((RD4(sc, SNVS_LPCR) & LPCR_SRTC_ENV) != enbit)
		continue;
}