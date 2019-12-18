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
struct vchan_info {int trigger; struct pcm_channel* channel; } ;
struct pcm_channel {struct pcm_channel* parentchannel; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_INSERT_HEAD (struct pcm_channel*,struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_N_TRIGGER ; 
 int /*<<< orphan*/  CHN_REMOVE (struct pcm_channel*,struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 scalar_t__ VCHAN_SYNC_REQUIRED (struct pcm_channel*) ; 
 TYPE_1__ children ; 
 int chn_notify (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int vchan_sync (struct pcm_channel*) ; 

__attribute__((used)) static int
vchan_trigger(kobj_t obj, void *data, int go)
{
	struct vchan_info *info;
	struct pcm_channel *c, *p;
	int ret, otrigger;

	info = data;

	if (!PCMTRIG_COMMON(go) || go == info->trigger)
		return (0);

	c = info->channel;
	p = c->parentchannel;
	otrigger = info->trigger;
	info->trigger = go;

	CHN_LOCKASSERT(c);

	CHN_UNLOCK(c);
	CHN_LOCK(p);

	switch (go) {
	case PCMTRIG_START:
		if (otrigger != PCMTRIG_START)
			CHN_INSERT_HEAD(p, c, children.busy);
		break;
	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		if (otrigger == PCMTRIG_START)
			CHN_REMOVE(p, c, children.busy);
		break;
	default:
		break;
	}

	ret = chn_notify(p, CHN_N_TRIGGER);

	CHN_LOCK(c);

	if (ret == 0 && go == PCMTRIG_START && VCHAN_SYNC_REQUIRED(c))
		ret = vchan_sync(c);

	CHN_UNLOCK(c);
	CHN_UNLOCK(p);
	CHN_LOCK(c);

	return (ret);
}