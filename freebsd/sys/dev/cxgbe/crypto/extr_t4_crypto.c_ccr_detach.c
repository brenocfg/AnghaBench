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
struct ccr_softc {int detaching; TYPE_1__* adapter; int /*<<< orphan*/  sg_crp; int /*<<< orphan*/  sg_ulptx; int /*<<< orphan*/  sg_dsgl; int /*<<< orphan*/  iv_aad_buf; int /*<<< orphan*/  sg_iv_aad; int /*<<< orphan*/  lock; int /*<<< orphan*/  cid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ccr_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CCR ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct ccr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccr_detach(device_t dev)
{
	struct ccr_softc *sc;

	sc = device_get_softc(dev);

	mtx_lock(&sc->lock);
	sc->detaching = true;
	mtx_unlock(&sc->lock);

	crypto_unregister_all(sc->cid);

	mtx_destroy(&sc->lock);
	sglist_free(sc->sg_iv_aad);
	free(sc->iv_aad_buf, M_CCR);
	sglist_free(sc->sg_dsgl);
	sglist_free(sc->sg_ulptx);
	sglist_free(sc->sg_crp);
	sc->adapter->ccr_softc = NULL;
	return (0);
}