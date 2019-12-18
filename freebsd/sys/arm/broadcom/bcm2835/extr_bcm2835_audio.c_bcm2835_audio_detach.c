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
struct bcm2835_audio_info {scalar_t__ worker_state; int /*<<< orphan*/  worker_cv; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUDIO_LOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  BCM2835_AUDIO_UNLOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ WORKER_STOPPED ; 
 scalar_t__ WORKER_STOPPING ; 
 int /*<<< orphan*/  bcm2835_audio_release (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bcm2835_audio_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 struct bcm2835_audio_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm2835_audio_detach(device_t dev)
{
	int r;
	struct bcm2835_audio_info *sc;
	sc = pcm_getdevinfo(dev);

	/* Stop worker thread */
	BCM2835_AUDIO_LOCK(sc);
	sc->worker_state = WORKER_STOPPING;
	cv_signal(&sc->worker_cv);
	/* Wait for thread to exit */
	while (sc->worker_state != WORKER_STOPPED)
		cv_wait_sig(&sc->worker_cv, &sc->lock);
	BCM2835_AUDIO_UNLOCK(sc);

	r = pcm_unregister(dev);
	if (r)
		return r;

	mtx_destroy(&sc->lock);
	cv_destroy(&sc->worker_cv);

	bcm2835_audio_release(sc);

    	free(sc, M_DEVBUF);

	return 0;
}