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
typedef  int u8 ;
struct wpa_supplicant {scalar_t__** tspecs; } ;

/* Variables and functions */
 int TS_DIR_IDX_COUNT ; 
 int WMM_AC_NUM ; 

__attribute__((used)) static u8 wmm_ac_get_tspecs_count(struct wpa_supplicant *wpa_s)
{
	int ac, dir, tspecs_count = 0;

	for (ac = 0; ac < WMM_AC_NUM; ac++) {
		for (dir = 0; dir < TS_DIR_IDX_COUNT; dir++) {
			if (wpa_s->tspecs[ac][dir])
				tspecs_count++;
		}
	}

	return tspecs_count;
}