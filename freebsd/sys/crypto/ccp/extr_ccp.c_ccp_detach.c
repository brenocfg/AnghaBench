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
struct ccp_softc {int detaching; int hw_features; int /*<<< orphan*/  lock; int /*<<< orphan*/  cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int VERSION_CAP_TRNG ; 
 int /*<<< orphan*/  ccp_free_queues (struct ccp_softc*) ; 
 int /*<<< orphan*/  ccp_hw_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct ccp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct ccp_softc* g_ccp_softc ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_ccp ; 
 int /*<<< orphan*/  random_source_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ccp_detach(device_t dev)
{
	struct ccp_softc *sc;

	sc = device_get_softc(dev);

	mtx_lock(&sc->lock);
	sc->detaching = true;
	mtx_unlock(&sc->lock);

	crypto_unregister_all(sc->cid);
	if (g_ccp_softc == sc && (sc->hw_features & VERSION_CAP_TRNG) != 0)
		random_source_deregister(&random_ccp);

	ccp_hw_detach(dev);
	ccp_free_queues(sc);

	if (g_ccp_softc == sc)
		g_ccp_softc = NULL;

	mtx_destroy(&sc->lock);
	return (0);
}