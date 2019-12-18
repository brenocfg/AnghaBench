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
typedef  int uint32_t ;
struct pcmchan_matrix {scalar_t__ channels; scalar_t__ ext; scalar_t__ mask; scalar_t__* offset; TYPE_1__* map; } ;
struct TYPE_2__ {size_t type; scalar_t__ members; } ;

/* Variables and functions */
 int SND_CHN_T_END ; 
 size_t SND_CHN_T_MAX ; 

int
feeder_matrix_compare(struct pcmchan_matrix *m_in, struct pcmchan_matrix *m_out)
{
	uint32_t i;

	if (m_in == m_out)
		return (0);

	if (m_in->channels != m_out->channels || m_in->ext != m_out->ext ||
	    m_in->mask != m_out->mask)
		return (1);

	for (i = 0; i < (sizeof(m_in->map) / sizeof(m_in->map[0])); i++) {
		if (m_in->map[i].type != m_out->map[i].type)
			return (1);
		if (m_in->map[i].type == SND_CHN_T_MAX)
			break;
		if (m_in->map[i].members != m_out->map[i].members)
			return (1);
		if (i <= SND_CHN_T_END) {
			if (m_in->offset[m_in->map[i].type] !=
			    m_out->offset[m_out->map[i].type])
				return (1);
		}
	}

	return (0);
}