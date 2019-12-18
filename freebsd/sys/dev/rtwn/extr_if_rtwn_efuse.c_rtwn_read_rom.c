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
struct rtwn_softc {int /*<<< orphan*/  efuse_maplen; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtwn_efuse_read_prepare (struct rtwn_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_parse_rom (struct rtwn_softc*,int /*<<< orphan*/ *) ; 

int
rtwn_read_rom(struct rtwn_softc *sc)
{
	uint8_t *rom;
	int error;

	rom = malloc(sc->efuse_maplen, M_TEMP, M_WAITOK);

	/* Read full ROM image. */
	RTWN_LOCK(sc);
	error = rtwn_efuse_read_prepare(sc, rom, sc->efuse_maplen);
	RTWN_UNLOCK(sc);
	if (error != 0)
		goto fail;

	/* Parse & save data in softc. */
	rtwn_parse_rom(sc, rom);

fail:
	free(rom, M_TEMP);

	return (error);
}