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
typedef  scalar_t__ u8 ;
struct wpa_supplicant {scalar_t__** tspecs; } ;
typedef  enum ts_dir_idx { ____Placeholder_ts_dir_idx } ts_dir_idx ;

/* Variables and functions */
 int TS_DIR_IDX_COUNT ; 
 int WMM_AC_NUM ; 
 scalar_t__ wmm_ac_get_tsid (scalar_t__) ; 

__attribute__((used)) static int wmm_ac_find_tsid(struct wpa_supplicant *wpa_s, u8 tsid,
			    enum ts_dir_idx *dir)
{
	int ac;
	enum ts_dir_idx idx;

	for (ac = 0; ac < WMM_AC_NUM; ac++) {
		for (idx = 0; idx < TS_DIR_IDX_COUNT; idx++) {
			if (wpa_s->tspecs[ac][idx] &&
			    wmm_ac_get_tsid(wpa_s->tspecs[ac][idx]) == tsid) {
				if (dir)
					*dir = idx;
				return ac;
			}
		}
	}

	return -1;
}