#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct bcm2835_audio_info {TYPE_1__ pch; } ;
struct bcm2835_audio_chinfo {int /*<<< orphan*/  retrieved_samples; int /*<<< orphan*/  submitted_samples; struct bcm2835_audio_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  bcm2835_worker_play_start (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  bcm2835_worker_play_stop (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcmchan_trigger(kobj_t obj, void *data, int go)
{
	struct bcm2835_audio_chinfo *ch = data;
	struct bcm2835_audio_info *sc = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return (0);

	switch (go) {
	case PCMTRIG_START:
		/* kickstart data flow */
		chn_intr(sc->pch.channel);
		ch->submitted_samples = 0;
		ch->retrieved_samples = 0;
		bcm2835_worker_play_start(sc);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		bcm2835_worker_play_stop(sc);
		break;

	default:
		break;
	}
	return 0;
}