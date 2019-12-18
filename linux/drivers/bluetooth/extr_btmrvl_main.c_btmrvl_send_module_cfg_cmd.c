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
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CMD_MODULE_CFG_REQ ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int btmrvl_send_sync_cmd (struct btmrvl_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int btmrvl_send_module_cfg_cmd(struct btmrvl_private *priv, u8 subcmd)
{
	int ret;

	ret = btmrvl_send_sync_cmd(priv, BT_CMD_MODULE_CFG_REQ, &subcmd, 1);
	if (ret)
		BT_ERR("module_cfg_cmd(%x) failed", subcmd);

	return ret;
}