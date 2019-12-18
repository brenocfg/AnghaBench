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
struct pcm_channel {int flags; int /*<<< orphan*/  xruns; int /*<<< orphan*/  feeder; struct snd_dbuf* bufsoft; struct snd_dbuf* bufhard; } ;

/* Variables and functions */
 int CHN_F_MMAP ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_wakeup (struct pcm_channel*) ; 
 int /*<<< orphan*/  sndbuf_dispose (struct snd_dbuf*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sndbuf_feed (struct snd_dbuf*,struct snd_dbuf*,struct pcm_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sndbuf_getfree (struct snd_dbuf*) ; 
 unsigned int sndbuf_getready (struct snd_dbuf*) ; 

__attribute__((used)) static void
chn_rdfeed(struct pcm_channel *c)
{
    	struct snd_dbuf *b = c->bufhard;
    	struct snd_dbuf *bs = c->bufsoft;
	unsigned int amt;

	CHN_LOCKASSERT(c);

	if (c->flags & CHN_F_MMAP)
		sndbuf_dispose(bs, NULL, sndbuf_getready(bs));

	amt = sndbuf_getfree(bs);
	if (amt > 0)
		sndbuf_feed(b, bs, c, c->feeder, amt);

	amt = sndbuf_getready(b);
	if (amt > 0) {
		c->xruns++;
		sndbuf_dispose(b, NULL, amt);
	}

	if (sndbuf_getready(bs) > 0)
		chn_wakeup(c);
}