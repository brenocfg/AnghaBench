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
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  carp_list ; 
 int /*<<< orphan*/  carp_mod_cleanup () ; 
 int carp_mod_load () ; 
 int /*<<< orphan*/  carp_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
carp_modevent(module_t mod, int type, void *data)
{
	switch (type) {
	case MOD_LOAD:
		return carp_mod_load();
		/* NOTREACHED */
	case MOD_UNLOAD:
		mtx_lock(&carp_mtx);
		if (LIST_EMPTY(&carp_list))
			carp_mod_cleanup();
		else {
			mtx_unlock(&carp_mtx);
			return (EBUSY);
		}
		break;

	default:
		return (EINVAL);
	}

	return (0);
}