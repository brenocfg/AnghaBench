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
struct tws_softc {int /*<<< orphan*/  tws_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_I2O0_HOBDBC ; 
 int /*<<< orphan*/  TWS_I2O0_IOBDB ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_reset (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tws_intr_attn_error(struct tws_softc *sc)
{
    u_int32_t db=0;

    TWS_TRACE(sc, "attn error", 0, 0);
    tws_write_reg(sc, TWS_I2O0_HOBDBC, ~0, 4);
    db = tws_read_reg(sc, TWS_I2O0_IOBDB, 4);
    device_printf(sc->tws_dev, "Micro controller error.\n");
    tws_reset(sc);
}