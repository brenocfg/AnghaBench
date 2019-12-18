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
struct snd_dbuf {int dummy; } ;
struct pcm_channel {int flags; struct snd_dbuf* bufsoft; struct snd_dbuf* bufhard; } ;

/* Variables and functions */
 int CHN_F_ABORTING ; 
 int CHN_F_TRIGGERED ; 
 int CHN_F_VIRTUAL ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 scalar_t__ CHN_STOPPED (struct pcm_channel*) ; 
 int /*<<< orphan*/  PCMTRIG_ABORT ; 
 int /*<<< orphan*/  chn_dmaupdate (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_trigger (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int sndbuf_getready (struct snd_dbuf*) ; 
 int /*<<< orphan*/  sndbuf_setrun (struct snd_dbuf*,int /*<<< orphan*/ ) ; 

int
chn_abort(struct pcm_channel *c)
{
    	int missing = 0;
    	struct snd_dbuf *b = c->bufhard;
    	struct snd_dbuf *bs = c->bufsoft;

	CHN_LOCKASSERT(c);
	if (CHN_STOPPED(c))
		return 0;
	c->flags |= CHN_F_ABORTING;

	c->flags &= ~CHN_F_TRIGGERED;
	/* kill the channel */
	chn_trigger(c, PCMTRIG_ABORT);
	sndbuf_setrun(b, 0);
	if (!(c->flags & CHN_F_VIRTUAL))
		chn_dmaupdate(c);
    	missing = sndbuf_getready(bs);

	c->flags &= ~CHN_F_ABORTING;
	return missing;
}