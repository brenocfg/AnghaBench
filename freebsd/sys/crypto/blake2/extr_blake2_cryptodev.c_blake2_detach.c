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
struct blake2_softc {int dying; int /*<<< orphan*/  lock; int /*<<< orphan*/  cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  blake2_cleanctx () ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct blake2_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
blake2_detach(device_t dev)
{
	struct blake2_softc *sc;

	sc = device_get_softc(dev);

	rw_wlock(&sc->lock);
	sc->dying = true;
	rw_wunlock(&sc->lock);
	crypto_unregister_all(sc->cid);

	rw_destroy(&sc->lock);

	blake2_cleanctx();

	return (0);
}