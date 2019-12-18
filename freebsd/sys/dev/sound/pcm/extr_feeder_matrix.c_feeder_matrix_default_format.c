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
typedef  scalar_t__ uint32_t ;
struct pcmchan_matrix {scalar_t__ ext; } ;
struct TYPE_2__ {scalar_t__ channels; scalar_t__ ext; } ;

/* Variables and functions */
 scalar_t__ AFMT_CHANNEL (scalar_t__) ; 
 scalar_t__ AFMT_EXTCHANNEL (scalar_t__) ; 
 scalar_t__ SND_CHN_MATRIX_BEGIN ; 
 scalar_t__ SND_CHN_MATRIX_END ; 
 scalar_t__ SND_FORMAT (scalar_t__,scalar_t__,scalar_t__) ; 
 struct pcmchan_matrix* feeder_matrix_default_channel_map (scalar_t__) ; 
 TYPE_1__* feeder_matrix_maps ; 

uint32_t
feeder_matrix_default_format(uint32_t format)
{
	struct pcmchan_matrix *m;
	uint32_t i, ch, ext;

	ch = AFMT_CHANNEL(format);
	ext = AFMT_EXTCHANNEL(format);

	if (ext != 0) {
		for (i = SND_CHN_MATRIX_BEGIN; i <= SND_CHN_MATRIX_END; i++) {
			if (feeder_matrix_maps[i].channels == ch &&
			    feeder_matrix_maps[i].ext == ext)
			return (SND_FORMAT(format, ch, ext));
		}
	}

	m = feeder_matrix_default_channel_map(ch);
	if (m == NULL)
		return (0x00000000);

	return (SND_FORMAT(format, ch, m->ext));
}