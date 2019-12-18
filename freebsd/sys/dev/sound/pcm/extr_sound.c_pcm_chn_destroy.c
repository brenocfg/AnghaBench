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
struct snddev_info {int dummy; } ;
struct pcm_channel {int /*<<< orphan*/  methods; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct snddev_info* parentsnddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int chn_kill (struct pcm_channel*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pcm_chn_destroy(struct pcm_channel *ch)
{
	struct snddev_info *d;
	int err;

	d = ch->parentsnddev;
	PCM_BUSYASSERT(d);

	err = chn_kill(ch);
	if (err) {
		device_printf(ch->dev, "chn_kill(%s) failed, err = %d\n",
		    ch->name, err);
		return (err);
	}

	kobj_delete(ch->methods, M_DEVBUF);
	free(ch, M_DEVBUF);

	return (0);
}