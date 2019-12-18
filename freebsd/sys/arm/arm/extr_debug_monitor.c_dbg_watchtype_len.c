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
typedef  int uint32_t ;

/* Variables and functions */
#define  DBG_WB_CTRL_LEN_1 131 
#define  DBG_WB_CTRL_LEN_2 130 
#define  DBG_WB_CTRL_LEN_4 129 
#define  DBG_WB_CTRL_LEN_8 128 

__attribute__((used)) static int
dbg_watchtype_len(uint32_t len)
{

	switch (len) {
	case DBG_WB_CTRL_LEN_1:
		return (1);
	case DBG_WB_CTRL_LEN_2:
		return (2);
	case DBG_WB_CTRL_LEN_4:
		return (4);
	case DBG_WB_CTRL_LEN_8:
		return (8);
	default:
		return (0);
	}
}