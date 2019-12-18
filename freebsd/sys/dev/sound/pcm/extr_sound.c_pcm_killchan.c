#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snddev_info {int dummy; } ;
struct pcm_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcm; } ;

/* Variables and functions */
 struct pcm_channel* CHN_FIRST (struct snddev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_LOCK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCK (struct snddev_info*) ; 
 TYPE_1__ channels ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcm_chn_destroy (struct pcm_channel*) ; 
 int pcm_chn_remove (struct snddev_info*,struct pcm_channel*) ; 

__attribute__((used)) static int
pcm_killchan(device_t dev)
{
	struct snddev_info *d = device_get_softc(dev);
	struct pcm_channel *ch;
	int error;

	PCM_BUSYASSERT(d);

	ch = CHN_FIRST(d, channels.pcm);

	PCM_LOCK(d);
	error = pcm_chn_remove(d, ch);
	PCM_UNLOCK(d);
	if (error)
		return (error);
	return (pcm_chn_destroy(ch));
}