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
typedef  scalar_t__ time_t ;
struct tws_softc {int dummy; } ;
typedef  int boolean ;

/* Variables and functions */
 int TWS_BIT13 ; 
 int /*<<< orphan*/  TWS_I2O0_SCRPD3 ; 
 scalar_t__ TWS_LOCAL_TIME ; 
 scalar_t__ TWS_RESET_TIMEOUT ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_assert_soft_reset (struct tws_softc*) ; 
 scalar_t__ tws_ctlr_ready (struct tws_softc*) ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 

boolean
tws_ctlr_reset(struct tws_softc *sc)
{

    u_int32_t reg;
    time_t endt;
    /* int i=0; */

    TWS_TRACE_DEBUG(sc, "entry", 0, 0);

    tws_assert_soft_reset(sc);

    do {
        reg = tws_read_reg(sc, TWS_I2O0_SCRPD3, 4);
    } while ( reg & TWS_BIT13 );

    endt = TWS_LOCAL_TIME + TWS_RESET_TIMEOUT;
    do {
        if(tws_ctlr_ready(sc))
            return(true);
    } while (TWS_LOCAL_TIME <= endt);
    return(false);

}