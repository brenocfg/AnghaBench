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
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  als_playback_start (struct sc_chinfo*) ; 
 int /*<<< orphan*/  als_playback_stop (struct sc_chinfo*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alspchan_trigger(kobj_t obj, void *data, int go)
{
	struct	sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	snd_mtxlock(sc->lock);
	switch(go) {
	case PCMTRIG_START:
		als_playback_start(ch);
		break;
	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		als_playback_stop(ch);
		break;
	default:
		break;
	}
	snd_mtxunlock(sc->lock);
	return 0;
}