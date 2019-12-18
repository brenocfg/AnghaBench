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
typedef  int u_int32_t ;
struct tws_softc {int dummy; } ;

/* Variables and functions */
 int TWS_BIT2 ; 
 int /*<<< orphan*/  TWS_I2O0_HIMASK ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int,int) ; 

void
tws_enable_db_intr(struct tws_softc *sc)
{
    u_int32_t reg;

    TWS_TRACE_DEBUG(sc, "entry", 0, 0);
    reg = tws_read_reg(sc, TWS_I2O0_HIMASK, 4);
    reg = reg & ~TWS_BIT2;
    tws_write_reg(sc, TWS_I2O0_HIMASK, reg, 4);
}