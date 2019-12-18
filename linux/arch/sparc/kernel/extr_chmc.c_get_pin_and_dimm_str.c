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
struct TYPE_2__ {int* dimm_map; int* pin_map; } ;
struct jbusmc_obp_mem_layout {char** dimm_labels; TYPE_1__ map; } ;
struct chmc_obp_mem_layout {char** dimm_labels; struct chmc_obp_map* map; scalar_t__ symmetric; } ;
struct chmc_obp_map {int* dimm_map; int* pin_map; } ;

/* Variables and functions */
 int JBUS_LAST_BIT ; 
 unsigned long L2_LINE_ADDR_MSK ; 
 scalar_t__ MC_TYPE_JBUS ; 
 int QW_BITS ; 
 unsigned long QW_BYTES ; 
 int SAFARI_LAST_BIT ; 
 scalar_t__ mc_type ; 
 int syndrome_to_qword_code (int) ; 

__attribute__((used)) static void get_pin_and_dimm_str(int syndrome_code, unsigned long paddr,
				 int *pin_p, char **dimm_str_p, void *_prop,
				 int base_dimm_offset)
{
	int qword_code = syndrome_to_qword_code(syndrome_code);
	int cache_line_offset;
	int offset_inverse;
	int dimm_map_index;
	int map_val;

	if (mc_type == MC_TYPE_JBUS) {
		struct jbusmc_obp_mem_layout *p = _prop;

		/* JBUS */
		cache_line_offset = qword_code;
		offset_inverse = (JBUS_LAST_BIT - cache_line_offset);
		dimm_map_index = offset_inverse / 8;
		map_val = p->map.dimm_map[dimm_map_index];
		map_val = ((map_val >> ((7 - (offset_inverse & 7)))) & 1);
		*dimm_str_p = p->dimm_labels[base_dimm_offset + map_val];
		*pin_p = p->map.pin_map[cache_line_offset];
	} else {
		struct chmc_obp_mem_layout *p = _prop;
		struct chmc_obp_map *mp;
		int qword;

		/* Safari */
		if (p->symmetric)
			mp = &p->map[0];
		else
			mp = &p->map[1];

		qword = (paddr & L2_LINE_ADDR_MSK) / QW_BYTES;
		cache_line_offset = ((3 - qword) * QW_BITS) + qword_code;
		offset_inverse = (SAFARI_LAST_BIT - cache_line_offset);
		dimm_map_index = offset_inverse >> 2;
		map_val = mp->dimm_map[dimm_map_index];
		map_val = ((map_val >> ((3 - (offset_inverse & 3)) << 1)) & 0x3);
		*dimm_str_p = p->dimm_labels[base_dimm_offset + map_val];
		*pin_p = mp->pin_map[cache_line_offset];
	}
}