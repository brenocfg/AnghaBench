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

/* Variables and functions */
 int /*<<< orphan*/  IB_PC_EXT_COUNTER_SELECT2_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_LAST_F ; 
 int /*<<< orphan*/  IB_PC_EXT_FIRST_F ; 
 int /*<<< orphan*/  IB_PC_EXT_LAST_F ; 
 int _dump_fields (char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mad_dump_perfcounters_ext(char *buf, int bufsz, void *val, int valsz)
{
	int cnt;

	cnt = _dump_fields(buf, bufsz, val, IB_PC_EXT_FIRST_F, IB_PC_EXT_LAST_F);
	if (cnt < 0)
		return;

	 _dump_fields(buf + cnt, bufsz - cnt, val,
		      IB_PC_EXT_COUNTER_SELECT2_F, IB_PC_EXT_ERR_LAST_F);
}