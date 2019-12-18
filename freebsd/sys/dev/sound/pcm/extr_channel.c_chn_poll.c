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
struct thread {int dummy; } ;
struct snd_dbuf {int dummy; } ;
struct pcm_channel {int flags; struct snd_dbuf* bufsoft; } ;

/* Variables and functions */
 int CHN_F_MMAP ; 
 int CHN_F_TRIGGERED ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_pollreset (struct pcm_channel*) ; 
 scalar_t__ chn_polltrigger (struct pcm_channel*) ; 
 int chn_start (struct pcm_channel*,int) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_getsel (struct snd_dbuf*) ; 

int
chn_poll(struct pcm_channel *c, int ev, struct thread *td)
{
	struct snd_dbuf *bs = c->bufsoft;
	int ret;

	CHN_LOCKASSERT(c);

    	if (!(c->flags & (CHN_F_MMAP | CHN_F_TRIGGERED))) {
		ret = chn_start(c, 1);
		if (ret != 0)
			return (0);
	}

	ret = 0;
	if (chn_polltrigger(c)) {
		chn_pollreset(c);
		ret = ev;
	} else
		selrecord(td, sndbuf_getsel(bs));

	return (ret);
}