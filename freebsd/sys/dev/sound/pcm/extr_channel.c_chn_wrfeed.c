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
 int CHN_F_CLOSING ; 
 int CHN_F_MMAP ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_wakeup (struct pcm_channel*) ; 
 unsigned int imax (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sndbuf_acquire (struct snd_dbuf*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sndbuf_feed (struct snd_dbuf*,struct snd_dbuf*,struct pcm_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sndbuf_getfree (struct snd_dbuf*) ; 
 unsigned int sndbuf_getready (struct snd_dbuf*) ; 
 unsigned int sndbuf_getsize (struct snd_dbuf*) ; 
 scalar_t__ sndbuf_xbytes (unsigned int,struct snd_dbuf*,struct snd_dbuf*) ; 

__attribute__((used)) static void
chn_wrfeed(struct pcm_channel *c)
{
    	struct snd_dbuf *b = c->bufhard;
    	struct snd_dbuf *bs = c->bufsoft;
	unsigned int amt, want, wasfree;

	CHN_LOCKASSERT(c);

	if ((c->flags & CHN_F_MMAP) && !(c->flags & CHN_F_CLOSING))
		sndbuf_acquire(bs, NULL, sndbuf_getfree(bs));

	wasfree = sndbuf_getfree(b);
	want = min(sndbuf_getsize(b),
	    imax(0, sndbuf_xbytes(sndbuf_getsize(bs), bs, b) -
	     sndbuf_getready(b)));
	amt = min(wasfree, want);
	if (amt > 0)
		sndbuf_feed(bs, b, c, c->feeder, amt);

	/*
	 * Possible xruns. There should be no empty space left in buffer.
	 */
	if (sndbuf_getready(b) < want)
		c->xruns++;

	if (sndbuf_getfree(b) < wasfree)
		chn_wakeup(c);
}