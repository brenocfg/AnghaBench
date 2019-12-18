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
struct rdr_tbl_ent {int dummy; } ;

/* Variables and functions */
 scalar_t__ ONYX_INTF ; 
 scalar_t__ perf_processor_interface ; 
 struct rdr_tbl_ent const* perf_rdr_tbl_U ; 
 struct rdr_tbl_ent const* perf_rdr_tbl_W ; 

__attribute__((used)) static const struct rdr_tbl_ent * perf_rdr_get_entry(uint32_t rdr_num)
{
	if (perf_processor_interface == ONYX_INTF) {
		return &perf_rdr_tbl_U[rdr_num];
	} else {
		return &perf_rdr_tbl_W[rdr_num];
	}
}