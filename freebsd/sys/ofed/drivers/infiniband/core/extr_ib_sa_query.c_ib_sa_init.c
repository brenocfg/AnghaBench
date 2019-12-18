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
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int ib_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int mcast_init () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  tid ; 

int ib_sa_init(void)
{
	int ret;

	get_random_bytes(&tid, sizeof tid);

	ret = ib_register_client(&sa_client);
	if (ret) {
		pr_err("Couldn't register ib_sa client\n");
		goto err1;
	}

	ret = mcast_init();
	if (ret) {
		pr_err("Couldn't initialize multicast handling\n");
		goto err2;
	}

	return 0;

err2:
	ib_unregister_client(&sa_client);
err1:
	return ret;
}