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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  txerrors; int /*<<< orphan*/  (* task_15s ) (struct bwn_mac*) ;} ;
struct TYPE_3__ {scalar_t__ opensource; } ;
struct bwn_mac {TYPE_2__ mac_phy; TYPE_1__ mac_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_SCRATCH ; 
 int /*<<< orphan*/  BWN_TXERROR_MAX ; 
 int /*<<< orphan*/  BWN_WATCHDOG_REG ; 
 int /*<<< orphan*/  bwn_restart (struct bwn_mac*,char*) ; 
 scalar_t__ bwn_shm_read_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_task_15s(struct bwn_mac *mac)
{
	uint16_t reg;

	if (mac->mac_fw.opensource) {
		reg = bwn_shm_read_2(mac, BWN_SCRATCH, BWN_WATCHDOG_REG);
		if (reg) {
			bwn_restart(mac, "fw watchdog");
			return;
		}
		bwn_shm_write_2(mac, BWN_SCRATCH, BWN_WATCHDOG_REG, 1);
	}
	if (mac->mac_phy.task_15s)
		mac->mac_phy.task_15s(mac);

	mac->mac_phy.txerrors = BWN_TXERROR_MAX;
}