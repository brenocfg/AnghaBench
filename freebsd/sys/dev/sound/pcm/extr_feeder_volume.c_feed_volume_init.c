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
typedef  size_t uint32_t ;
struct pcmchan_matrix {int dummy; } ;
struct pcm_feeder {struct feed_volume_info* data; TYPE_1__* desc; } ;
struct feed_volume_info {scalar_t__ channels; int /*<<< orphan*/  state; int /*<<< orphan*/  volume_class; int /*<<< orphan*/  apply; int /*<<< orphan*/  bps; } ;
struct TYPE_4__ {scalar_t__ format; int /*<<< orphan*/  apply; } ;
struct TYPE_3__ {scalar_t__ in; scalar_t__ out; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_BPS (scalar_t__) ; 
 scalar_t__ AFMT_CHANNEL (scalar_t__) ; 
 scalar_t__ AFMT_ENCODING (scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEEDVOLUME_ENABLE ; 
 size_t FEEDVOLUME_TAB_SIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ SND_CHN_MAX ; 
 int /*<<< orphan*/  SND_VOL_C_PCM ; 
 TYPE_2__* feed_volume_info_tab ; 
 struct pcmchan_matrix* feeder_matrix_default_channel_map (scalar_t__) ; 
 int feeder_volume_apply_matrix (struct pcm_feeder*,struct pcmchan_matrix*) ; 
 int /*<<< orphan*/  free (struct feed_volume_info*,int /*<<< orphan*/ ) ; 
 struct feed_volume_info* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
feed_volume_init(struct pcm_feeder *f)
{
	struct feed_volume_info *info;
	struct pcmchan_matrix *m;
	uint32_t i;
	int ret;

	if (f->desc->in != f->desc->out ||
	    AFMT_CHANNEL(f->desc->in) > SND_CHN_MAX)
		return (EINVAL);

	for (i = 0; i < FEEDVOLUME_TAB_SIZE; i++) {
		if (AFMT_ENCODING(f->desc->in) ==
		    feed_volume_info_tab[i].format) {
			info = malloc(sizeof(*info), M_DEVBUF,
			    M_NOWAIT | M_ZERO);
			if (info == NULL)
				return (ENOMEM);

			info->bps = AFMT_BPS(f->desc->in);
			info->channels = AFMT_CHANNEL(f->desc->in);
			info->apply = feed_volume_info_tab[i].apply;
			info->volume_class = SND_VOL_C_PCM;
			info->state = FEEDVOLUME_ENABLE;

			f->data = info;
			m = feeder_matrix_default_channel_map(info->channels);
			if (m == NULL) {
				free(info, M_DEVBUF);
				return (EINVAL);
			}

			ret = feeder_volume_apply_matrix(f, m);
			if (ret != 0)
				free(info, M_DEVBUF);

			return (ret);
		}
	}

	return (EINVAL);
}