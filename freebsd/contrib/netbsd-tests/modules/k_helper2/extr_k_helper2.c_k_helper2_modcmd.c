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
typedef  int modcmd_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  MODULE_CMD_FINI 130 
#define  MODULE_CMD_INIT 129 
#define  MODULE_CMD_STAT 128 
 int k_helper2_fini (void*) ; 
 int k_helper2_init (void*) ; 

__attribute__((used)) static
int
k_helper2_modcmd(modcmd_t cmd, void *arg)
{
	int ret;

	switch (cmd) {
	case MODULE_CMD_INIT:
		ret = k_helper2_init(arg);
		break;

	case MODULE_CMD_FINI:
		ret = k_helper2_fini(arg);
		break;

	case MODULE_CMD_STAT:
	default:
		ret = ENOTTY;
	}

	return ret;
}