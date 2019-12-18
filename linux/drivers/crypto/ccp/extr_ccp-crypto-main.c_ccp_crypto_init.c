#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cmd_count; int /*<<< orphan*/  cmds; int /*<<< orphan*/ * backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ccp_present () ; 
 int ccp_register_algs () ; 
 int /*<<< orphan*/  ccp_unregister_algs () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ req_queue ; 
 int /*<<< orphan*/  req_queue_lock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccp_crypto_init(void)
{
	int ret;

	ret = ccp_present();
	if (ret) {
		pr_err("Cannot load: there are no available CCPs\n");
		return ret;
	}

	spin_lock_init(&req_queue_lock);
	INIT_LIST_HEAD(&req_queue.cmds);
	req_queue.backlog = &req_queue.cmds;
	req_queue.cmd_count = 0;

	ret = ccp_register_algs();
	if (ret)
		ccp_unregister_algs();

	return ret;
}