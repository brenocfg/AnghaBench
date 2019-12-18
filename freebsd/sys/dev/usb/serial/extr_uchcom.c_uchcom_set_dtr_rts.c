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
struct uchcom_softc {scalar_t__ sc_version; scalar_t__ sc_rts; scalar_t__ sc_dtr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCHCOM_DTR_MASK ; 
 int /*<<< orphan*/  UCHCOM_RTS_MASK ; 
 scalar_t__ UCHCOM_VER_20 ; 
 int /*<<< orphan*/  uchcom_set_dtr_rts_10 (struct uchcom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchcom_set_dtr_rts_20 (struct uchcom_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uchcom_set_dtr_rts(struct uchcom_softc *sc)
{
	uint8_t val = 0;

	if (sc->sc_dtr)
		val |= UCHCOM_DTR_MASK;
	if (sc->sc_rts)
		val |= UCHCOM_RTS_MASK;

	if (sc->sc_version < UCHCOM_VER_20)
		uchcom_set_dtr_rts_10(sc, ~val);
	else
		uchcom_set_dtr_rts_20(sc, ~val);
}