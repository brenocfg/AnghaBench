#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  size_t u_int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  reqs_errored; int /*<<< orphan*/  reqs_out; } ;
struct tws_softc {TYPE_2__* reqs; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cb ) (TYPE_2__*) ;} ;

/* Variables and functions */
 size_t TWS_INVALID_REQID ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  tws_err_complete (struct tws_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ tws_get_response (struct tws_softc*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tws_intr_resp(struct tws_softc *sc)
{
    u_int16_t req_id;
    u_int64_t mfa;

    while ( tws_get_response(sc, &req_id, &mfa) ) {
        sc->stats.reqs_out++;
        if ( req_id == TWS_INVALID_REQID ) {
            TWS_TRACE_DEBUG(sc, "invalid req_id", mfa, req_id);
            sc->stats.reqs_errored++;
            tws_err_complete(sc, mfa);
            continue;
        }
        sc->reqs[req_id].cb(&sc->reqs[req_id]);
    }

}