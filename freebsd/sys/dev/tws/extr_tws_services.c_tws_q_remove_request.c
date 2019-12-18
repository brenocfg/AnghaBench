#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
struct tws_softc {struct tws_request** q_head; struct tws_request** q_tail; int /*<<< orphan*/  q_lock; } ;
struct tws_request {size_t request_id; TYPE_1__* prev; struct tws_request* next; } ;
struct TYPE_2__ {struct tws_request* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tws_request* tws_q_remove_head (struct tws_softc*,size_t) ; 
 struct tws_request* tws_q_remove_tail (struct tws_softc*,size_t) ; 

struct tws_request *
tws_q_remove_request(struct tws_softc *sc, struct tws_request *req,
                                 u_int8_t q_type )
{

    struct tws_request *r;

    mtx_assert(&sc->q_lock, MA_OWNED);
    if ( req == NULL ) {
        TWS_TRACE_DEBUG(sc, "null req", 0, q_type);
        return(NULL);
    }

    if ( req == sc->q_head[q_type] )
        return(tws_q_remove_head(sc, q_type));
    if ( req == sc->q_tail[q_type] )
        return(tws_q_remove_tail(sc, q_type));


    /* The given node is not at head or tail.
     * It's in the middle and there are more than
     * 2 elements on the q.
     */

    if ( req->next == NULL || req->prev == NULL ) {
        TWS_TRACE_DEBUG(sc, "invalid req", 0, q_type);
        return(NULL);
    }

/* debug only */
    r = sc->q_head[q_type];
    while ( r ) {
        if ( req == r )
            break;
        r = r->next;
    } 

    if ( !r ) {
        TWS_TRACE_DEBUG(sc, "req not in q", 0, req->request_id);
        return(NULL);
    }
/* debug end */

    req->prev->next = r->next;
    req->next->prev = r->prev;
    req->next = NULL;
    req->prev = NULL;
    return(req);
}