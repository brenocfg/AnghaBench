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
struct pst_softc {TYPE_2__* iop; int /*<<< orphan*/  queue; } ;
struct bio {TYPE_1__* bio_disk; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_3__ {struct pst_softc* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pst_start (struct pst_softc*) ; 

__attribute__((used)) static void
pststrategy(struct bio *bp)
{
    struct pst_softc *psc = bp->bio_disk->d_drv1;
    
    mtx_lock(&psc->iop->mtx);
    bioq_disksort(&psc->queue, bp);
    pst_start(psc);
    mtx_unlock(&psc->iop->mtx);
}