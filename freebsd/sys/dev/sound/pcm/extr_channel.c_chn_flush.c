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
struct pcm_channel {scalar_t__ direction; int flags; struct snd_dbuf* bufhard; } ;

/* Variables and functions */
 int CHN_F_CLOSING ; 
 int CHN_F_TRIGGERED ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMTRIG_ABORT ; 
 int /*<<< orphan*/  chn_sync (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chn_trigger (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sndbuf_setrun (struct snd_dbuf*,int /*<<< orphan*/ ) ; 

int
chn_flush(struct pcm_channel *c)
{
    	struct snd_dbuf *b = c->bufhard;

	CHN_LOCKASSERT(c);
	KASSERT(c->direction == PCMDIR_PLAY, ("chn_flush on bad channel"));
    	DEB(printf("chn_flush: c->flags 0x%08x\n", c->flags));

	c->flags |= CHN_F_CLOSING;
	chn_sync(c, 0);
	c->flags &= ~CHN_F_TRIGGERED;
	/* kill the channel */
	chn_trigger(c, PCMTRIG_ABORT);
	sndbuf_setrun(b, 0);

    	c->flags &= ~CHN_F_CLOSING;
    	return 0;
}