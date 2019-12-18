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
typedef  size_t uint32_t ;
struct pcmchan_matrix {size_t channels; size_t ext; } ;

/* Variables and functions */
 size_t AFMT_CHANNEL (size_t) ; 
 size_t AFMT_EXTCHANNEL (size_t) ; 
 size_t SND_CHN_MATRIX_BEGIN ; 
 size_t SND_CHN_MATRIX_END ; 
 struct pcmchan_matrix* feeder_matrix_maps ; 

struct pcmchan_matrix *
feeder_matrix_format_map(uint32_t format)
{
	uint32_t i, ch, ext;

	ch = AFMT_CHANNEL(format);
	ext = AFMT_EXTCHANNEL(format);

	for (i = SND_CHN_MATRIX_BEGIN; i <= SND_CHN_MATRIX_END; i++) {
		if (feeder_matrix_maps[i].channels == ch &&
		    feeder_matrix_maps[i].ext == ext)
			return (&feeder_matrix_maps[i]);
	}

	return (NULL);
}