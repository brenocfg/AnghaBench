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
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_EFUSE_ACCESS ; 
 int /*<<< orphan*/  R92C_EFUSE_ACCESS_OFF ; 
 int rtwn_efuse_read (struct rtwn_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtwn_efuse_switch_power (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_efuse_read_prepare(struct rtwn_softc *sc, uint8_t *rom, uint16_t size)
{
	int error;

	error = rtwn_efuse_switch_power(sc);
	if (error != 0)
		goto fail;

	error = rtwn_efuse_read(sc, rom, size);

fail:
	rtwn_write_1(sc, R92C_EFUSE_ACCESS, R92C_EFUSE_ACCESS_OFF);

	return (error);
}