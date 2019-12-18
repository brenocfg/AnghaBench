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
#define  MOD_LOAD 130 
#define  MOD_QUIESCE 129 
#define  MOD_UNLOAD 128 
 int iscsi_load () ; 
 int iscsi_quiesce () ; 
 int iscsi_unload () ; 

__attribute__((used)) static int
iscsi_modevent(module_t mod, int what, void *arg)
{
	int error;

	switch (what) {
	case MOD_LOAD:
		error = iscsi_load();
		break;
	case MOD_UNLOAD:
		error = iscsi_unload();
		break;
	case MOD_QUIESCE:
		error = iscsi_quiesce();
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}