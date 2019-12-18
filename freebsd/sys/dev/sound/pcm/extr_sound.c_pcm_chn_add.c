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
struct snddev_info {int /*<<< orphan*/  devcount; int /*<<< orphan*/  rvchancount; int /*<<< orphan*/  reccount; int /*<<< orphan*/  pvchancount; int /*<<< orphan*/  playcount; } ;
struct pcm_channel {scalar_t__ direction; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcm; } ;

/* Variables and functions */
 int CHN_DEV (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_INSERT_SORT_ASCEND (struct snddev_info*,struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_LOCKASSERT (struct snddev_info*) ; 
#define  SND_DEV_DSPHW_PLAY 131 
#define  SND_DEV_DSPHW_REC 130 
#define  SND_DEV_DSPHW_VPLAY 129 
#define  SND_DEV_DSPHW_VREC 128 
 TYPE_1__ channels ; 

int
pcm_chn_add(struct snddev_info *d, struct pcm_channel *ch)
{
	PCM_BUSYASSERT(d);
	PCM_LOCKASSERT(d);
	KASSERT(ch != NULL && (ch->direction == PCMDIR_PLAY ||
	    ch->direction == PCMDIR_REC), ("Invalid pcm channel"));

	CHN_INSERT_SORT_ASCEND(d, ch, channels.pcm);

	switch (CHN_DEV(ch)) {
	case SND_DEV_DSPHW_PLAY:
		d->playcount++;
		break;
	case SND_DEV_DSPHW_VPLAY:
		d->pvchancount++;
		break;
	case SND_DEV_DSPHW_REC:
		d->reccount++;
		break;
	case SND_DEV_DSPHW_VREC:
		d->rvchancount++;
		break;
	default:
		break;
	}

	d->devcount++;

	return (0);
}