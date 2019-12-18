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
struct xbb_softc {int /*<<< orphan*/  xb_io_lock; int /*<<< orphan*/  connected; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_STATE_SUSPENDED ; 
 struct xbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xbb_suspend(device_t dev)
{
#ifdef NOT_YET
        struct xbb_softc *sc = device_get_softc(dev);

        /* Prevent new requests being issued until we fix things up. */
        mtx_lock(&sc->xb_io_lock);
        sc->connected = BLKIF_STATE_SUSPENDED;
        mtx_unlock(&sc->xb_io_lock);
#endif

        return (0);
}