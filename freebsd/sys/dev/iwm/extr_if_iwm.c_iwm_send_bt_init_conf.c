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
struct iwm_softc {int dummy; } ;
struct iwm_bt_coex_cmd {void* enabled_modules; void* mode; } ;
typedef  int /*<<< orphan*/  bt_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_BT_COEX_HIGH_BAND_RET ; 
 int /*<<< orphan*/  IWM_BT_COEX_WIFI ; 
 int /*<<< orphan*/  IWM_BT_CONFIG ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_bt_coex_cmd*) ; 

__attribute__((used)) static int
iwm_send_bt_init_conf(struct iwm_softc *sc)
{
	struct iwm_bt_coex_cmd bt_cmd;

	bt_cmd.mode = htole32(IWM_BT_COEX_WIFI);
	bt_cmd.enabled_modules = htole32(IWM_BT_COEX_HIGH_BAND_RET);

	return iwm_mvm_send_cmd_pdu(sc, IWM_BT_CONFIG, 0, sizeof(bt_cmd),
	    &bt_cmd);
}