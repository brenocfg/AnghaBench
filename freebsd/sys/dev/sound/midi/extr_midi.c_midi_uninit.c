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
struct snd_midi {int /*<<< orphan*/  lock; scalar_t__ wchan; scalar_t__ rchan; scalar_t__ busy; } ;

/* Variables and functions */
 int EBUSY ; 
 int midi_destroy (struct snd_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midistat_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
midi_uninit(struct snd_midi *m)
{
	int err;

	err = EBUSY;
	sx_xlock(&midistat_lock);
	mtx_lock(&m->lock);
	if (m->busy) {
		if (!(m->rchan || m->wchan))
			goto err;

		if (m->rchan) {
			wakeup(&m->rchan);
			m->rchan = 0;
		}
		if (m->wchan) {
			wakeup(&m->wchan);
			m->wchan = 0;
		}
	}
	err = midi_destroy(m, 0);
	if (!err)
		goto exit;

err:
	mtx_unlock(&m->lock);
exit:
	sx_xunlock(&midistat_lock);
	return err;
}