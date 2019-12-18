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
struct uaudio_chan {struct pcmchan_caps pcm_cap; } ;

/* Variables and functions */

struct pcmchan_caps *
uaudio_chan_getcaps(struct uaudio_chan *ch)
{
	return (&ch->pcm_cap);
}