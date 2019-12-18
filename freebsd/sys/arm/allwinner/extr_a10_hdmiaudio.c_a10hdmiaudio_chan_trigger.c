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
struct a10hdmiaudio_info {int /*<<< orphan*/  lock; } ;
struct a10hdmiaudio_chinfo {int run; struct a10hdmiaudio_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  a10hdmiaudio_start (struct a10hdmiaudio_chinfo*) ; 
 int /*<<< orphan*/  a10hdmiaudio_stop (struct a10hdmiaudio_chinfo*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10hdmiaudio_chan_trigger(kobj_t obj, void *data, int go)
{
	struct a10hdmiaudio_chinfo *ch = data;
	struct a10hdmiaudio_info *sc = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return (0);

	snd_mtxlock(sc->lock);
	switch (go) {
	case PCMTRIG_START:
		ch->run = 1;
		a10hdmiaudio_start(ch);
		break;
	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		ch->run = 0;
		a10hdmiaudio_stop(ch);
		break;
	default:
		break;
	}
	snd_mtxunlock(sc->lock);

	return (0);
}