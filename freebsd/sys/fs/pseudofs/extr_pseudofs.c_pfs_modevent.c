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
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  pfs_vncache_load () ; 
 int /*<<< orphan*/  pfs_vncache_unload () ; 

__attribute__((used)) static int
pfs_modevent(module_t mod, int evt, void *arg)
{
	switch (evt) {
	case MOD_LOAD:
		pfs_vncache_load();
		break;
	case MOD_UNLOAD:
	case MOD_SHUTDOWN:
		pfs_vncache_unload();
		break;
	default:
		return EOPNOTSUPP;
		break;
	}
	return 0;
}