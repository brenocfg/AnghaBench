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
typedef  int /*<<< orphan*/  uint32_t ;
struct snd_dbuf {int dummy; } ;
struct emu_voice {int start; int ismaster; int vol; struct emu_voice* slave; int /*<<< orphan*/ * vbuf; int /*<<< orphan*/  buf; scalar_t__ running; scalar_t__ stereo; scalar_t__ b16; scalar_t__ speed; scalar_t__ end; } ;
struct emu_sc_info {int dbg_level; int /*<<< orphan*/  mem; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int EMUPAGESIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* emu_memalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emu_memfree (int /*<<< orphan*/ *,void*) ; 
 int emu_memstart (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sndbuf_setup (struct snd_dbuf*,void*,int /*<<< orphan*/ ) ; 

int
emu_vinit(struct emu_sc_info *sc, struct emu_voice *m, struct emu_voice *s,
    uint32_t sz, struct snd_dbuf *b)
{
	void *vbuf;
	bus_addr_t tmp_addr;

	vbuf = emu_memalloc(&sc->mem, sz, &tmp_addr, "vinit");
	if (vbuf == NULL) {
		if(sc->dbg_level > 2)
			device_printf(sc->dev, "emu_memalloc returns NULL in enu_vinit\n");
		return (ENOMEM);
		}
	if (b != NULL)
		sndbuf_setup(b, vbuf, sz);
	m->start = emu_memstart(&sc->mem, vbuf) * EMUPAGESIZE;
	if (m->start < 0) {
		if(sc->dbg_level > 2)
			device_printf(sc->dev, "emu_memstart returns (-1) in enu_vinit\n");
		emu_memfree(&sc->mem, vbuf);
		return (ENOMEM);
	}
	m->end = m->start + sz;
	m->speed = 0;
	m->b16 = 0;
	m->stereo = 0;
	m->running = 0;
	m->ismaster = 1;
	m->vol = 0xff;
	m->buf = tmp_addr;
	m->vbuf = vbuf;
	m->slave = s;
	if (s != NULL) {
		s->start = m->start;
		s->end = m->end;
		s->speed = 0;
		s->b16 = 0;
		s->stereo = 0;
		s->running = 0;
		s->ismaster = 0;
		s->vol = m->vol;
		s->buf = m->buf;
		s->vbuf = NULL;
		s->slave = NULL;
	}
	return (0);
}