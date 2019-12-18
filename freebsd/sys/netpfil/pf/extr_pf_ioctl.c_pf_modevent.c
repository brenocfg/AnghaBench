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
 int EINVAL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int pf_load () ; 

__attribute__((used)) static int
pf_modevent(module_t mod, int type, void *data)
{
	int error = 0;

	switch(type) {
	case MOD_LOAD:
		error = pf_load();
		break;
	case MOD_UNLOAD:
		/* Handled in SYSUNINIT(pf_unload) to ensure it's done after
		 * the vnet_pf_uninit()s */
		break;
	default:
		error = EINVAL;
		break;
	}

	return (error);
}