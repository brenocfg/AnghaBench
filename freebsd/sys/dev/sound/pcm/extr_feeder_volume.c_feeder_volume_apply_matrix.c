#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pcmchan_matrix {int channels; TYPE_2__* map; } ;
struct pcm_feeder {struct feed_volume_info* data; TYPE_1__* desc; } ;
struct feed_volume_info {int channels; int /*<<< orphan*/ * matrix; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FEEDER_VOLUME ; 
 int SND_CHN_MAX ; 
 int SND_CHN_MIN ; 
 int /*<<< orphan*/  SND_CHN_T_FL ; 

int
feeder_volume_apply_matrix(struct pcm_feeder *f, struct pcmchan_matrix *m)
{
	struct feed_volume_info *info;
	uint32_t i;

	if (f == NULL || f->desc == NULL || f->desc->type != FEEDER_VOLUME ||
	    f->data == NULL || m == NULL || m->channels < SND_CHN_MIN ||
	    m->channels > SND_CHN_MAX)
		return (EINVAL);

	info = f->data;

	for (i = 0; i < (sizeof(info->matrix) / sizeof(info->matrix[0])); i++) {
		if (i < m->channels)
			info->matrix[i] = m->map[i].type;
		else
			info->matrix[i] = SND_CHN_T_FL;
	}

	info->channels = m->channels;

	return (0);
}