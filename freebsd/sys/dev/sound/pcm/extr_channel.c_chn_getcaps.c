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
struct pcmchan_caps {int dummy; } ;
struct pcm_channel {int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 struct pcmchan_caps* CHANNEL_GETCAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 

struct pcmchan_caps *
chn_getcaps(struct pcm_channel *c)
{
	CHN_LOCKASSERT(c);
	return CHANNEL_GETCAPS(c->methods, c->devinfo);
}