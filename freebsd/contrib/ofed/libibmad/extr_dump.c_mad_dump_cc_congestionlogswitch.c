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
 int /*<<< orphan*/  IB_CC_CONGESTION_LOG_SWITCH_FIRST_F ; 
 int /*<<< orphan*/  IB_CC_CONGESTION_LOG_SWITCH_LAST_F ; 
 int /*<<< orphan*/  _dump_fields (char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mad_dump_cc_congestionlogswitch(char *buf, int bufsz, void *val, int valsz)
{
	_dump_fields(buf, bufsz, val, IB_CC_CONGESTION_LOG_SWITCH_FIRST_F,
		     IB_CC_CONGESTION_LOG_SWITCH_LAST_F);
}