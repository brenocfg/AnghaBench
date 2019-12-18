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
struct tws_softc {struct tws_request* reqs; } ;
struct tws_request {scalar_t__ state; void* error_code; int /*<<< orphan*/  data; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TWS ; 
 void* TWS_REQ_RET_RESET ; 
 scalar_t__ TWS_REQ_STATE_BUSY ; 
 scalar_t__ TWS_REQ_STATE_FREE ; 
 size_t TWS_REQ_TYPE_AEN_FETCH ; 
 size_t TWS_REQ_TYPE_GETSET_PARAM ; 
 size_t TWS_REQ_TYPE_PASSTHRU ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_unmap_request (struct tws_softc*,struct tws_request*) ; 

__attribute__((used)) static void
tws_drain_reserved_reqs(struct tws_softc *sc)
{
    struct tws_request *r;

    r = &sc->reqs[TWS_REQ_TYPE_AEN_FETCH];
    if ( r->state != TWS_REQ_STATE_FREE ) {
        TWS_TRACE_DEBUG(sc, "reset aen req", 0, 0);
	callout_stop(&r->timeout);
        tws_unmap_request(sc, r);
        free(r->data, M_TWS);
        r->state = TWS_REQ_STATE_FREE;
        r->error_code = TWS_REQ_RET_RESET;
    } 

    r = &sc->reqs[TWS_REQ_TYPE_PASSTHRU];
    if ( r->state == TWS_REQ_STATE_BUSY ) {
        TWS_TRACE_DEBUG(sc, "reset passthru req", 0, 0);
        r->error_code = TWS_REQ_RET_RESET;
    } 

    r = &sc->reqs[TWS_REQ_TYPE_GETSET_PARAM];
    if ( r->state != TWS_REQ_STATE_FREE ) {
        TWS_TRACE_DEBUG(sc, "reset setparam req", 0, 0);
	callout_stop(&r->timeout);
        tws_unmap_request(sc, r);
        free(r->data, M_TWS);
        r->state = TWS_REQ_STATE_FREE;
        r->error_code = TWS_REQ_RET_RESET;
    } 
}