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
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct tws_softc {int is64bit; int obfl_q_overrun; } ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int TWS_FIFO_EMPTY32 ; 
 int /*<<< orphan*/  TWS_I2O0_HOBDBC ; 
 int /*<<< orphan*/  TWS_I2O0_IOPOBQPH ; 
 int /*<<< orphan*/  TWS_I2O0_IOPOBQPL ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,...) ; 
 int /*<<< orphan*/  tws_display_ctlr_info (struct tws_softc*) ; 
 scalar_t__ tws_init_connect (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_init_obfl_q (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_queue_depth ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_turn_on_interrupts (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int 
tws_init_ctlr(struct tws_softc *sc)
{
    u_int64_t reg;
    u_int32_t regh, regl;

    TWS_TRACE_DEBUG(sc, "entry", sc, sc->is64bit);
    sc->obfl_q_overrun = false;
    if ( tws_init_connect(sc, tws_queue_depth) )
    {
        TWS_TRACE_DEBUG(sc, "initConnect failed", 0, sc->is64bit);
        return(FAILURE);
        
    }


    while( 1 ) {
        regh = tws_read_reg(sc, TWS_I2O0_IOPOBQPH, 4);
        regl = tws_read_reg(sc, TWS_I2O0_IOPOBQPL, 4);
        reg = (((u_int64_t)regh) << 32) | regl;
        TWS_TRACE_DEBUG(sc, "host outbound cleanup",reg, regl);
        if ( regh == TWS_FIFO_EMPTY32 )
            break;
    } 

    tws_init_obfl_q(sc);
    tws_display_ctlr_info(sc);
    tws_write_reg(sc, TWS_I2O0_HOBDBC, ~0, 4);
    tws_turn_on_interrupts(sc);
    return(SUCCESS);
}