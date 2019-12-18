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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bcm2835_audio_chinfo {scalar_t__ playback_state; int spd; int fmt; scalar_t__ available_space; int unsubmittedptr; int submitted_samples; int /*<<< orphan*/  buffer; } ;
struct bcm2835_audio_info {scalar_t__ worker_state; scalar_t__ flags_pending; int volume; int dest; int /*<<< orphan*/  worker_cv; struct bcm2835_audio_chinfo pch; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AUDIO_PARAMS ; 
 int AUDIO_PLAY ; 
 int AUDIO_STOP ; 
 int /*<<< orphan*/  BCM2835_AUDIO_LOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  BCM2835_AUDIO_UNLOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PLAYBACK_IDLE ; 
 scalar_t__ PLAYBACK_PLAYING ; 
 int VCHIQ_AUDIO_PACKET_SIZE ; 
 scalar_t__ WORKER_RUNNING ; 
 scalar_t__ WORKER_STOPPED ; 
 scalar_t__ bcm2835_audio_buffer_should_sleep (struct bcm2835_audio_chinfo*) ; 
 int /*<<< orphan*/  bcm2835_audio_reset_channel (struct bcm2835_audio_chinfo*) ; 
 int /*<<< orphan*/  bcm2835_audio_start (struct bcm2835_audio_chinfo*) ; 
 int /*<<< orphan*/  bcm2835_audio_stop (struct bcm2835_audio_chinfo*) ; 
 int /*<<< orphan*/  bcm2835_audio_update_controls (struct bcm2835_audio_info*,int,int) ; 
 int /*<<< orphan*/  bcm2835_audio_update_params (struct bcm2835_audio_info*,int,int) ; 
 int /*<<< orphan*/  bcm2835_audio_write_samples (struct bcm2835_audio_chinfo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ sndbuf_getbuf (int /*<<< orphan*/ ) ; 
 scalar_t__ sndbuf_getready (int /*<<< orphan*/ ) ; 
 int sndbuf_getreadyptr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm2835_audio_worker(void *data)
{
	struct bcm2835_audio_info *sc = (struct bcm2835_audio_info *)data;
	struct bcm2835_audio_chinfo *ch = &sc->pch;
	uint32_t speed, format;
	uint32_t volume, dest;
	uint32_t flags;
	uint32_t count, size, readyptr;
	uint8_t *buf;

	ch->playback_state = PLAYBACK_IDLE;

	while (1) {
		if (sc->worker_state != WORKER_RUNNING)
			break;

		BCM2835_AUDIO_LOCK(sc);
		/*
		 * wait until there are flags set or buffer is ready
		 * to consume more samples
		 */
		while ((sc->flags_pending == 0) &&
		    bcm2835_audio_buffer_should_sleep(ch)) {
			cv_wait_sig(&sc->worker_cv, &sc->lock);
		}
		flags = sc->flags_pending;
		/* Clear pending flags */
		sc->flags_pending = 0;
		BCM2835_AUDIO_UNLOCK(sc);

		/* Requested to change parameters */
		if (flags & AUDIO_PARAMS) {
			BCM2835_AUDIO_LOCK(sc);
			speed = ch->spd;
			format = ch->fmt;
			volume = sc->volume;
			dest = sc->dest;
			BCM2835_AUDIO_UNLOCK(sc);
			if (ch->playback_state == PLAYBACK_IDLE)
				bcm2835_audio_update_params(sc, format, speed);
			bcm2835_audio_update_controls(sc, volume, dest);
		}

		/* Requested to stop playback */
		if ((flags & AUDIO_STOP) &&
		    (ch->playback_state == PLAYBACK_PLAYING)) {
			bcm2835_audio_stop(ch);
			BCM2835_AUDIO_LOCK(sc);
			bcm2835_audio_reset_channel(&sc->pch);
			ch->playback_state = PLAYBACK_IDLE;
			BCM2835_AUDIO_UNLOCK(sc);
			continue;
		}

		/* Requested to start playback */
		if ((flags & AUDIO_PLAY) &&
		    (ch->playback_state == PLAYBACK_IDLE)) {
			BCM2835_AUDIO_LOCK(sc);
			ch->playback_state = PLAYBACK_PLAYING;
			BCM2835_AUDIO_UNLOCK(sc);
			bcm2835_audio_start(ch);
		}

		if (ch->playback_state == PLAYBACK_IDLE)
			continue;

		if (sndbuf_getready(ch->buffer) == 0)
			continue;

		count = sndbuf_getready(ch->buffer);
		size = sndbuf_getsize(ch->buffer);
		readyptr = sndbuf_getreadyptr(ch->buffer);

		BCM2835_AUDIO_LOCK(sc);
		if (readyptr + count > size)
			count = size - readyptr;
		count = min(count, ch->available_space);
		count -= (count % VCHIQ_AUDIO_PACKET_SIZE);
		BCM2835_AUDIO_UNLOCK(sc);

		if (count < VCHIQ_AUDIO_PACKET_SIZE)
			continue;

		buf = (uint8_t*)sndbuf_getbuf(ch->buffer) + readyptr;

		bcm2835_audio_write_samples(ch, buf, count);
		BCM2835_AUDIO_LOCK(sc);
		ch->unsubmittedptr = (ch->unsubmittedptr + count) % sndbuf_getsize(ch->buffer);
		ch->available_space -= count;
		ch->submitted_samples += count;
		KASSERT(ch->available_space >= 0, ("ch->available_space == %d\n", ch->available_space));
		BCM2835_AUDIO_UNLOCK(sc);
	}

	BCM2835_AUDIO_LOCK(sc);
	sc->worker_state = WORKER_STOPPED;
	cv_signal(&sc->worker_cv);
	BCM2835_AUDIO_UNLOCK(sc);

	kproc_exit(0);
}