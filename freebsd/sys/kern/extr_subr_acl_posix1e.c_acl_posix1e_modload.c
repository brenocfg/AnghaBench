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
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 

__attribute__((used)) static int
acl_posix1e_modload(module_t mod, int what, void *arg)
{
	int ret;

	ret = 0;

	switch (what) {
	case MOD_LOAD:
	case MOD_SHUTDOWN:
		break;

	case MOD_QUIESCE:
		/* XXX TODO */
		ret = 0;
		break;

	case MOD_UNLOAD:
		/* XXX TODO */
		ret = 0;
		break;
	default:
		ret = EINVAL;
		break;
	}

	return (ret);
}