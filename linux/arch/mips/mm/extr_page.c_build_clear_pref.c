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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  A0 ; 
 int /*<<< orphan*/  AT ; 
 int /*<<< orphan*/  Create_Dirty_Excl_D ; 
 int /*<<< orphan*/  Create_Dirty_Excl_SD ; 
 scalar_t__ R4600_V1_HIT_CACHEOP_WAR ; 
 scalar_t__ R4600_V2_HIT_CACHEOP_WAR ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  _uasm_i_pref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int cache_line_mask () ; 
 int cache_line_size ; 
 scalar_t__ cpu_has_cache_cdex_p ; 
 scalar_t__ cpu_has_cache_cdex_s ; 
 scalar_t__ cpu_is_r4600_v1_x () ; 
 scalar_t__ cpu_is_r4600_v2_x () ; 
 int half_clear_loop_size ; 
 scalar_t__ pref_bias_clear_store ; 
 int /*<<< orphan*/  pref_dst_mode ; 
 int /*<<< orphan*/  uasm_i_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 

__attribute__((used)) static inline void build_clear_pref(u32 **buf, int off)
{
	if (off & cache_line_mask())
		return;

	if (pref_bias_clear_store) {
		_uasm_i_pref(buf, pref_dst_mode, pref_bias_clear_store + off,
			    A0);
	} else if (cache_line_size == (half_clear_loop_size << 1)) {
		if (cpu_has_cache_cdex_s) {
			uasm_i_cache(buf, Create_Dirty_Excl_SD, off, A0);
		} else if (cpu_has_cache_cdex_p) {
			if (R4600_V1_HIT_CACHEOP_WAR && cpu_is_r4600_v1_x()) {
				uasm_i_nop(buf);
				uasm_i_nop(buf);
				uasm_i_nop(buf);
				uasm_i_nop(buf);
			}

			if (R4600_V2_HIT_CACHEOP_WAR && cpu_is_r4600_v2_x())
				uasm_i_lw(buf, ZERO, ZERO, AT);

			uasm_i_cache(buf, Create_Dirty_Excl_D, off, A0);
		}
	}
}