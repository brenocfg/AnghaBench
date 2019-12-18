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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_VERS_ADDR ; 
 int /*<<< orphan*/  FW_VERS_ADDR_PRE8 ; 
 int t3_read_flash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 

int t3_get_fw_version(adapter_t *adapter, u32 *vers)
{
	int ret = t3_read_flash(adapter, FW_VERS_ADDR, 1, vers, 0);
	if (!ret && *vers != 0xffffffff)
		return 0;
	else
		return t3_read_flash(adapter, FW_VERS_ADDR_PRE8, 1, vers, 0);
}