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
 int TWS_BIT8 ; 
 int /*<<< orphan*/  TWS_I2O0_HIBDB ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int,int /*<<< orphan*/ ) ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int,int) ; 

void
tws_assert_soft_reset(struct tws_softc *sc)
{
    u_int32_t reg;

    reg = tws_read_reg(sc, TWS_I2O0_HIBDB, 4);
    TWS_TRACE_DEBUG(sc, "in bound door bell read ", reg, TWS_I2O0_HIBDB);
    tws_write_reg(sc, TWS_I2O0_HIBDB, reg | TWS_BIT8, 4);

}