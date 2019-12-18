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
typedef  int uint32_t ;
struct pcmchan_caps {int /*<<< orphan*/  maxspeed; int /*<<< orphan*/  minspeed; } ;
struct pcm_channel {int format; int speed; int /*<<< orphan*/  bufhard; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int CHANNEL_SETFORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHANNEL_SETSPEED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 scalar_t__ CHN_STARTED (struct pcm_channel*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RANGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcmchan_caps* chn_getcaps (struct pcm_channel*) ; 
 int chn_resizebuf (struct pcm_channel*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int feeder_chain (struct pcm_channel*) ; 
 int feeder_rate_round ; 
 int /*<<< orphan*/  sndbuf_getfmt (int /*<<< orphan*/ ) ; 
 int sndbuf_getspd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_setspd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
chn_setparam(struct pcm_channel *c, uint32_t format, uint32_t speed)
{
	struct pcmchan_caps *caps;
	uint32_t hwspeed, delta;
	int ret;

	CHN_LOCKASSERT(c);

	if (speed < 1 || format == 0 || CHN_STARTED(c))
		return (EINVAL);

	c->format = format;
	c->speed = speed;

	caps = chn_getcaps(c);

	hwspeed = speed;
	RANGE(hwspeed, caps->minspeed, caps->maxspeed);

	sndbuf_setspd(c->bufhard, CHANNEL_SETSPEED(c->methods, c->devinfo,
	    hwspeed));
	hwspeed = sndbuf_getspd(c->bufhard);

	delta = (hwspeed > speed) ? (hwspeed - speed) : (speed - hwspeed);

	if (delta <= feeder_rate_round)
		c->speed = hwspeed;

	ret = feeder_chain(c);

	if (ret == 0)
		ret = CHANNEL_SETFORMAT(c->methods, c->devinfo,
		    sndbuf_getfmt(c->bufhard));

	if (ret == 0)
		ret = chn_resizebuf(c, -2, 0, 0);

	return (ret);
}