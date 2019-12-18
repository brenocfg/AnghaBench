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
typedef  int /*<<< orphan*/  u_int16_t ;
struct tws_softc {int dummy; } ;
struct tws_outbound_response {int /*<<< orphan*/  request_id; int /*<<< orphan*/  not_mfa; } ;
typedef  int boolean ;

/* Variables and functions */
 int TWS_FIFO_EMPTY32 ; 
 int /*<<< orphan*/  TWS_I2O0_HOBQPH ; 
 int /*<<< orphan*/  TWS_I2O0_HOBQPL ; 
 int /*<<< orphan*/  TWS_INVALID_REQID ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 

boolean
tws_get_response(struct tws_softc *sc, u_int16_t *req_id, u_int64_t *mfa) 
{
    u_int64_t out_mfa=0, val=0;
    struct tws_outbound_response out_res;

    *req_id = TWS_INVALID_REQID;
    out_mfa = (u_int64_t)tws_read_reg(sc, TWS_I2O0_HOBQPH, 4);

    if ( out_mfa == TWS_FIFO_EMPTY32 ) {
        return(false);

    }
    out_mfa = out_mfa << 32;
    val = tws_read_reg(sc, TWS_I2O0_HOBQPL, 4);
    out_mfa = out_mfa | val;
    
    out_res =  *(struct tws_outbound_response *)&out_mfa;

    if ( !out_res.not_mfa ) {
        *mfa = out_mfa;
        return(true);
    } else {
        *req_id = out_res.request_id;
    }
    
    return(true);
}