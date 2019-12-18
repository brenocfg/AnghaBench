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
struct uchcom_softc {int /*<<< orphan*/  sc_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchcom_get_version (struct uchcom_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uchcom_update_version(struct uchcom_softc *sc)
{
	uchcom_get_version(sc, &sc->sc_version);
	DPRINTF("Chip version: 0x%02x\n", sc->sc_version);
}