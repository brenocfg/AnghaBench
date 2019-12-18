#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hsmode; scalar_t__ hscmd; scalar_t__ pscmd; scalar_t__ hscfgcmd; } ;
struct btmrvl_private {int (* hw_wakeup_firmware ) (struct btmrvl_private*) ;TYPE_1__* adapter; TYPE_2__ btmrvl_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  HS_DEACTIVATED ; 
 int btmrvl_enable_hs (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_enable_ps (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_send_hscfg_cmd (struct btmrvl_private*) ; 
 int stub1 (struct btmrvl_private*) ; 

int btmrvl_prepare_command(struct btmrvl_private *priv)
{
	int ret = 0;

	if (priv->btmrvl_dev.hscfgcmd) {
		priv->btmrvl_dev.hscfgcmd = 0;
		btmrvl_send_hscfg_cmd(priv);
	}

	if (priv->btmrvl_dev.pscmd) {
		priv->btmrvl_dev.pscmd = 0;
		btmrvl_enable_ps(priv);
	}

	if (priv->btmrvl_dev.hscmd) {
		priv->btmrvl_dev.hscmd = 0;

		if (priv->btmrvl_dev.hsmode) {
			ret = btmrvl_enable_hs(priv);
		} else {
			ret = priv->hw_wakeup_firmware(priv);
			priv->adapter->hs_state = HS_DEACTIVATED;
			BT_DBG("BT: HS DEACTIVATED due to host activity!");
		}
	}

	return ret;
}