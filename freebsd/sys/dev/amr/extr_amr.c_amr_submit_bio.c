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
struct bio {int dummy; } ;
struct amr_softc {int /*<<< orphan*/  amr_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  amr_enqueue_bio (struct amr_softc*,struct bio*) ; 
 int /*<<< orphan*/  amr_startio (struct amr_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
amr_submit_bio(struct amr_softc *sc, struct bio *bio)
{
    debug_called(2);

    mtx_lock(&sc->amr_list_lock);
    amr_enqueue_bio(sc, bio);
    amr_startio(sc);
    mtx_unlock(&sc->amr_list_lock);
    return(0);
}