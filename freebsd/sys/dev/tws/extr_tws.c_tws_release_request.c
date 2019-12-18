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
struct tws_softc {int /*<<< orphan*/  q_lock; } ;
struct tws_request {struct tws_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_FREE_Q ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_q_insert_tail (struct tws_softc*,struct tws_request*,int /*<<< orphan*/ ) ; 

void
tws_release_request(struct tws_request *req)
{

    struct tws_softc *sc = req->sc;

    TWS_TRACE_DEBUG(sc, "entry", sc, 0);
    mtx_lock(&sc->q_lock);
    tws_q_insert_tail(sc, req, TWS_FREE_Q);
    mtx_unlock(&sc->q_lock);
}