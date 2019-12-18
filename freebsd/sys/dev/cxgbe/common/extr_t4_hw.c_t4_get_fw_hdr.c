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
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_hdr {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_FW_START ; 
 int t4_read_flash (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

int t4_get_fw_hdr(struct adapter *adapter, struct fw_hdr *hdr)
{
	return t4_read_flash(adapter, FLASH_FW_START,
	    sizeof (*hdr) / sizeof (uint32_t), (uint32_t *)hdr, 1);
}