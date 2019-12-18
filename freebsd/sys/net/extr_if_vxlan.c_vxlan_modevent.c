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
 int ENOTSUP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  vxlan_load () ; 
 int /*<<< orphan*/  vxlan_unload () ; 

__attribute__((used)) static int
vxlan_modevent(module_t mod, int type, void *unused)
{
	int error;

	error = 0;

	switch (type) {
	case MOD_LOAD:
		vxlan_load();
		break;
	case MOD_UNLOAD:
		vxlan_unload();
		break;
	default:
		error = ENOTSUP;
		break;
	}

	return (error);
}