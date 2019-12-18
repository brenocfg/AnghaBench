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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cache ; 
 int /*<<< orphan*/  family ; 
 scalar_t__ genl_connect (int /*<<< orphan*/ ) ; 
 int genl_ctrl_alloc_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genl_ctrl_search_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle ; 
 int /*<<< orphan*/  nl_socket_alloc () ; 
 int /*<<< orphan*/  swlib_priv_free () ; 

__attribute__((used)) static int
swlib_priv_init(void)
{
	int ret;

	handle = nl_socket_alloc();
	if (!handle) {
		DPRINTF("Failed to create handle\n");
		goto err;
	}

	if (genl_connect(handle)) {
		DPRINTF("Failed to connect to generic netlink\n");
		goto err;
	}

	ret = genl_ctrl_alloc_cache(handle, &cache);
	if (ret < 0) {
		DPRINTF("Failed to allocate netlink cache\n");
		goto err;
	}

	family = genl_ctrl_search_by_name(cache, "switch");
	if (!family) {
		DPRINTF("Switch API not present\n");
		goto err;
	}
	return 0;

err:
	swlib_priv_free();
	return -EINVAL;
}