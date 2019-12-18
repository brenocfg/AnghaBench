#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snddev_info {int /*<<< orphan*/  status; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ ack_count; scalar_t__ intr_count; int /*<<< orphan*/  hw_info; int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  card; } ;
typedef  TYPE_1__ oss_card_info ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCM_LOCK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_REGISTERED (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCKASSERT (struct snddev_info*) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ *) ; 
 struct snddev_info* devclass_get_softc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcm_devclass ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sound_oss_card_info(oss_card_info *si)
{
	struct snddev_info *d;
	int i, ncards;
	
	ncards = 0;

	for (i = 0; pcm_devclass != NULL &&
	    i < devclass_get_maxunit(pcm_devclass); i++) {
		d = devclass_get_softc(pcm_devclass, i);
		if (!PCM_REGISTERED(d))
			continue;

		if (ncards++ != si->card)
			continue;

		PCM_UNLOCKASSERT(d);
		PCM_LOCK(d);
		
		strlcpy(si->shortname, device_get_nameunit(d->dev),
		    sizeof(si->shortname));
		strlcpy(si->longname, device_get_desc(d->dev),
		    sizeof(si->longname));
		strlcpy(si->hw_info, d->status, sizeof(si->hw_info));
		si->intr_count = si->ack_count = 0;

		PCM_UNLOCK(d);

		return (0);
	}
	return (ENXIO);
}