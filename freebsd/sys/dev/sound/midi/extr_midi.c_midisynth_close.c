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
struct synth_midi {struct snd_midi* m; } ;
struct snd_midi {int synth_flags; int flags; int busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int ENXIO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_CALLBACK (struct snd_midi*,int /*<<< orphan*/ ,int) ; 
 int M_RX ; 
 int M_RXEN ; 
 int M_TX ; 
 int M_TXEN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
midisynth_close(void *n)
{
	struct snd_midi *m = ((struct synth_midi *)n)->m;
	int retval;
	int oldflags;

	MIDI_DEBUG(1, printf("midisynth_close %s %s\n",
	    m->synth_flags & FREAD ? "M_RX" : "",
	    m->synth_flags & FWRITE ? "M_TX" : ""));

	if (m == NULL)
		return ENXIO;

	mtx_lock(&m->lock);
	mtx_lock(&m->qlock);

	if ((m->synth_flags & FREAD && !(m->flags & M_RX)) ||
	    (m->synth_flags & FWRITE && !(m->flags & M_TX))) {
		retval = ENXIO;
		goto err;
	}
	m->busy--;

	oldflags = m->flags;

	if (m->synth_flags & FREAD)
		m->flags &= ~(M_RX | M_RXEN);
	if (m->synth_flags & FWRITE)
		m->flags &= ~M_TX;

	if ((m->flags & (M_TXEN | M_RXEN)) != (oldflags & (M_RXEN | M_TXEN)))
		MPU_CALLBACK(m, m->cookie, m->flags);

	MIDI_DEBUG(1, printf("midi_close: closed, busy = %d.\n", m->busy));

	mtx_unlock(&m->qlock);
	mtx_unlock(&m->lock);
	retval = 0;
err:	return retval;
}