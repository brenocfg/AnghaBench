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
struct tws_softc {struct tws_request** q_tail; struct tws_request** q_head; int /*<<< orphan*/  q_lock; } ;
struct tws_request {int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tws_insert2_empty_q(struct tws_softc *sc, struct tws_request *req, 
                                u_int8_t q_type )
{

    mtx_assert(&sc->q_lock, MA_OWNED);
    req->next = req->prev = NULL;
    sc->q_head[q_type] = sc->q_tail[q_type] = req;

}