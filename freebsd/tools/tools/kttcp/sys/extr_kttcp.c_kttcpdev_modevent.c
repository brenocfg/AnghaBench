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
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kttcp_cdevsw ; 
 int /*<<< orphan*/  kttcp_dev ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
kttcpdev_modevent(module_t mod, int type, void *unused)
{
	switch (type) {
	case MOD_LOAD:
		kttcp_dev = make_dev(&kttcp_cdevsw, 0,
				      UID_ROOT, GID_WHEEL, 0666,
				      "kttcp");
		return 0;
	case MOD_UNLOAD:
		/*XXX disallow if active sessions */
		destroy_dev(kttcp_dev);
		return 0;
	}
	return EINVAL;
}