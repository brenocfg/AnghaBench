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
typedef  int /*<<< orphan*/  u_int32_t ;
struct snd_dbuf {int dummy; } ;
struct sc_info {scalar_t__ audigy; } ;
struct emu_voice {int start; int ismaster; int vol; int fxrt1; int fxrt2; struct emu_voice* slave; int /*<<< orphan*/  buf; scalar_t__ running; scalar_t__ stereo; scalar_t__ b16; scalar_t__ speed; int /*<<< orphan*/ * channel; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int EMUPAGESIZE ; 
 int FXBUS_MIDI_CHORUS ; 
 int FXBUS_MIDI_REVERB ; 
 int FXBUS_PCM_LEFT ; 
 int FXBUS_PCM_RIGHT ; 
 void* emu_memalloc (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int emu_memstart (struct sc_info*,void*) ; 
 int /*<<< orphan*/  sndbuf_setup (struct snd_dbuf*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_vinit(struct sc_info *sc, struct emu_voice *m, struct emu_voice *s,
	  u_int32_t sz, struct snd_dbuf *b)
{
	void *buf;
	bus_addr_t tmp_addr;

	buf = emu_memalloc(sc, sz, &tmp_addr);
	if (buf == NULL)
		return -1;
	if (b != NULL)
		sndbuf_setup(b, buf, sz);
	m->start = emu_memstart(sc, buf) * EMUPAGESIZE;
	m->end = m->start + sz;
	m->channel = NULL;
	m->speed = 0;
	m->b16 = 0;
	m->stereo = 0;
	m->running = 0;
	m->ismaster = 1;
	m->vol = 0xff;
	m->buf = tmp_addr;
	m->slave = s;
	if (sc->audigy) {
		m->fxrt1 = FXBUS_MIDI_CHORUS | FXBUS_PCM_RIGHT << 8 |
		    FXBUS_PCM_LEFT << 16 | FXBUS_MIDI_REVERB << 24;
		m->fxrt2 = 0x3f3f3f3f;	/* No effects on second route */
	} else {
		m->fxrt1 = FXBUS_MIDI_CHORUS | FXBUS_PCM_RIGHT << 4 |
		    FXBUS_PCM_LEFT << 8 | FXBUS_MIDI_REVERB << 12;
		m->fxrt2 = 0;
	}

	if (s != NULL) {
		s->start = m->start;
		s->end = m->end;
		s->channel = NULL;
		s->speed = 0;
		s->b16 = 0;
		s->stereo = 0;
		s->running = 0;
		s->ismaster = 0;
		s->vol = m->vol;
		s->buf = m->buf;
		s->fxrt1 = m->fxrt1;
		s->fxrt2 = m->fxrt2;
		s->slave = NULL;
	}
	return 0;
}