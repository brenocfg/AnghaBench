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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL_KLD ; 
 int /*<<< orphan*/  NMG_LOCK_INIT () ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  netmap_cdevsw ; 
 int /*<<< orphan*/  netmap_dev ; 
 int /*<<< orphan*/  netmap_fini () ; 
 int netmap_init_bridges () ; 
 int netmap_mem_init () ; 
 int nm_os_ifnet_init () ; 
 int /*<<< orphan*/  nm_os_vi_init_index () ; 
 int /*<<< orphan*/  nm_prinf (char*) ; 

int
netmap_init(void)
{
	int error;

	NMG_LOCK_INIT();

	error = netmap_mem_init();
	if (error != 0)
		goto fail;
	/*
	 * MAKEDEV_ETERNAL_KLD avoids an expensive check on syscalls
	 * when the module is compiled in.
	 * XXX could use make_dev_credv() to get error number
	 */
	netmap_dev = make_dev_credf(MAKEDEV_ETERNAL_KLD,
		&netmap_cdevsw, 0, NULL, UID_ROOT, GID_WHEEL, 0600,
			      "netmap");
	if (!netmap_dev)
		goto fail;

	error = netmap_init_bridges();
	if (error)
		goto fail;

#ifdef __FreeBSD__
	nm_os_vi_init_index();
#endif

	error = nm_os_ifnet_init();
	if (error)
		goto fail;

	nm_prinf("netmap: loaded module");
	return (0);
fail:
	netmap_fini();
	return (EINVAL); /* may be incorrect */
}