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
typedef  scalar_t__ u_int ;
struct snd_dbuf {int dummy; } ;
struct pcm_channel {int flags; scalar_t__ lw; scalar_t__ direction; struct snd_dbuf* bufsoft; } ;

/* Variables and functions */
 int CHN_F_MMAP ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ sndbuf_getfree (struct snd_dbuf*) ; 
 scalar_t__ sndbuf_getprevtotal (struct snd_dbuf*) ; 
 scalar_t__ sndbuf_getready (struct snd_dbuf*) ; 
 scalar_t__ sndbuf_gettotal (struct snd_dbuf*) ; 

__attribute__((used)) static int
chn_polltrigger(struct pcm_channel *c)
{
	struct snd_dbuf *bs = c->bufsoft;
	u_int delta;

	CHN_LOCKASSERT(c);

	if (c->flags & CHN_F_MMAP) {
		if (sndbuf_getprevtotal(bs) < c->lw)
			delta = c->lw;
		else
			delta = sndbuf_gettotal(bs) - sndbuf_getprevtotal(bs);
	} else {
		if (c->direction == PCMDIR_PLAY)
			delta = sndbuf_getfree(bs);
		else
			delta = sndbuf_getready(bs);
	}

	return ((delta < c->lw) ? 0 : 1);
}