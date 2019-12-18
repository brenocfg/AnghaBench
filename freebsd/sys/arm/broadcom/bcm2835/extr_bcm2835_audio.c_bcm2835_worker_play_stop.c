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
struct bcm2835_audio_info {int /*<<< orphan*/  worker_cv; int /*<<< orphan*/  flags_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_PLAY ; 
 int /*<<< orphan*/  AUDIO_STOP ; 
 int /*<<< orphan*/  BCM2835_AUDIO_LOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  BCM2835_AUDIO_UNLOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bcm2835_worker_play_stop(struct bcm2835_audio_info *sc)
{
	BCM2835_AUDIO_LOCK(sc);
	sc->flags_pending &= ~(AUDIO_PLAY);
	sc->flags_pending |= AUDIO_STOP;
	cv_signal(&sc->worker_cv);
	BCM2835_AUDIO_UNLOCK(sc);
}