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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_FW6_PLD ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/ * do_cpl6_fw_pld ; 
 int /*<<< orphan*/  t4_register_cpl_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ccr_modevent(module_t mod, int cmd, void *arg)
{

	switch (cmd) {
	case MOD_LOAD:
		t4_register_cpl_handler(CPL_FW6_PLD, do_cpl6_fw_pld);
		return (0);
	case MOD_UNLOAD:
		t4_register_cpl_handler(CPL_FW6_PLD, NULL);
		return (0);
	default:
		return (EOPNOTSUPP);
	}
}