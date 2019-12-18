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
struct pcmchan_matrix {size_t channels; } ;

/* Variables and functions */
 size_t SND_CHN_MATRIX_BEGIN ; 
 size_t SND_CHN_MATRIX_END ; 
 size_t* feeder_matrix_default_ids ; 
 struct pcmchan_matrix* feeder_matrix_maps ; 

struct pcmchan_matrix *
feeder_matrix_default_channel_map(uint32_t ch)
{

	if (ch < feeder_matrix_maps[SND_CHN_MATRIX_BEGIN].channels ||
	    ch > feeder_matrix_maps[SND_CHN_MATRIX_END].channels)
		return (NULL);

	return (&feeder_matrix_maps[feeder_matrix_default_ids[ch]]);
}