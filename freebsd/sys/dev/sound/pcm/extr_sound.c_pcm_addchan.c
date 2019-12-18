#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snddev_info {int /*<<< orphan*/  dev; } ;
struct pcm_channel {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_LOCK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCK (struct snddev_info*) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int pcm_chn_add (struct snddev_info*,struct pcm_channel*) ; 
 struct pcm_channel* pcm_chn_create (struct snddev_info*,int /*<<< orphan*/ *,TYPE_1__*,int,int,void*) ; 
 int /*<<< orphan*/  pcm_chn_destroy (struct pcm_channel*) ; 

int
pcm_addchan(device_t dev, int dir, kobj_class_t cls, void *devinfo)
{
	struct snddev_info *d = device_get_softc(dev);
	struct pcm_channel *ch;
	int err;

	PCM_BUSYASSERT(d);

	PCM_LOCK(d);
	ch = pcm_chn_create(d, NULL, cls, dir, -1, devinfo);
	if (!ch) {
		device_printf(d->dev, "pcm_chn_create(%s, %d, %p) failed\n",
		    cls->name, dir, devinfo);
		PCM_UNLOCK(d);
		return (ENODEV);
	}

	err = pcm_chn_add(d, ch);
	PCM_UNLOCK(d);
	if (err) {
		device_printf(d->dev, "pcm_chn_add(%s) failed, err=%d\n",
		    ch->name, err);
		pcm_chn_destroy(ch);
	}

	return (err);
}