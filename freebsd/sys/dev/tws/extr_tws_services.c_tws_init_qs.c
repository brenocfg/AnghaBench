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
struct tws_softc {int /*<<< orphan*/  q_lock; int /*<<< orphan*/ ** q_tail; int /*<<< orphan*/ ** q_head; } ;

/* Variables and functions */
 int TWS_MAX_QS ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
tws_init_qs(struct tws_softc *sc)
{

    mtx_lock(&sc->q_lock);
    for(int i=0;i<TWS_MAX_QS;i++) {
        sc->q_head[i] = NULL;
        sc->q_tail[i] = NULL;
    }
    mtx_unlock(&sc->q_lock);

}