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
struct pcmchan_matrix {int dummy; } ;

/* Variables and functions */
 int SND_CHN_MATRIX_BEGIN ; 
 int SND_CHN_MATRIX_END ; 
 struct pcmchan_matrix* feeder_matrix_maps ; 

struct pcmchan_matrix *
feeder_matrix_id_map(int id)
{

	if (id < SND_CHN_MATRIX_BEGIN || id > SND_CHN_MATRIX_END)
		return (NULL);

	return (&feeder_matrix_maps[id]);
}