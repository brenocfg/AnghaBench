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
struct pcm_channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; struct snd_dbuf* bufsoft; struct snd_dbuf* bufhard; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_F_DEAD ; 
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 scalar_t__ CHN_STARTED (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  PCMTRIG_ABORT ; 
 int /*<<< orphan*/  chn_lockdestroy (struct pcm_channel*) ; 
 scalar_t__ chn_removefeeder (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_trigger (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_destroy (struct snd_dbuf*) ; 
 int /*<<< orphan*/  sndbuf_free (struct snd_dbuf*) ; 

int
chn_kill(struct pcm_channel *c)
{
    	struct snd_dbuf *b = c->bufhard;
    	struct snd_dbuf *bs = c->bufsoft;

	if (CHN_STARTED(c)) {
		CHN_LOCK(c);
		chn_trigger(c, PCMTRIG_ABORT);
		CHN_UNLOCK(c);
	}
	while (chn_removefeeder(c) == 0)
		;
	if (CHANNEL_FREE(c->methods, c->devinfo))
		sndbuf_free(b);
	sndbuf_destroy(bs);
	sndbuf_destroy(b);
	CHN_LOCK(c);
	c->flags |= CHN_F_DEAD;
	chn_lockdestroy(c);

	return (0);
}