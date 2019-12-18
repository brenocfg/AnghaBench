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
typedef  size_t u_int8_t ;
struct tws_softc {struct tws_request** q_head; int /*<<< orphan*/ ** q_tail; int /*<<< orphan*/  q_lock; } ;
struct tws_request {int /*<<< orphan*/ * prev; struct tws_request* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct tws_request *
tws_q_remove_head(struct tws_softc *sc, u_int8_t q_type )
{

    struct tws_request *r;

    mtx_assert(&sc->q_lock, MA_OWNED);
    r = sc->q_head[q_type];
    if ( !r ) 
        return(NULL);
    if ( r->next == NULL &&  r->prev == NULL ) {
        /* last element  */
        sc->q_head[q_type] = sc->q_tail[q_type] = NULL;
    } else {
        sc->q_head[q_type] = r->next;
        r->next->prev = NULL;
        r->next = NULL;
        r->prev = NULL;
    }
    return(r);
}