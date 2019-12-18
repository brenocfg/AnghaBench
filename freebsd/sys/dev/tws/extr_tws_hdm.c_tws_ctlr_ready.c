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
typedef  int boolean ;

/* Variables and functions */
 int TWS_BIT13 ; 
 int /*<<< orphan*/  TWS_I2O0_SCRPD3 ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 

boolean
tws_ctlr_ready(struct tws_softc *sc)
{
    u_int32_t reg;

    reg = tws_read_reg(sc, TWS_I2O0_SCRPD3, 4);
    if ( reg & TWS_BIT13 )
        return(true);
    else
        return(false);
}