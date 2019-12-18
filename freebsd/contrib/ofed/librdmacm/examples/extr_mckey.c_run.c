#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cma_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_addr; TYPE_2__* nodes; int /*<<< orphan*/  cmathread; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dst_in; int /*<<< orphan*/  src_in; } ;

/* Variables and functions */
 int addr_handler (TYPE_2__*) ; 
 int /*<<< orphan*/  cma_thread ; 
 int /*<<< orphan*/  connect_error () ; 
 int connect_events () ; 
 int connections ; 
 int /*<<< orphan*/  dst_addr ; 
 int get_addr (scalar_t__,struct sockaddr*) ; 
 int get_dst_addr (int /*<<< orphan*/ ,struct sockaddr*) ; 
 scalar_t__ is_sender ; 
 scalar_t__ message_count ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll_cqs () ; 
 int post_sends (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdma_bind_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_leave_multicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_resolve_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ src_addr ; 
 TYPE_1__ test ; 
 scalar_t__ unmapped_addr ; 

__attribute__((used)) static int run(void)
{
	int i, ret, err;

	printf("mckey: starting %s\n", is_sender ? "client" : "server");
	if (src_addr) {
		ret = get_addr(src_addr, (struct sockaddr *) &test.src_in);
		if (ret)
			return ret;
	}

	ret = get_dst_addr(dst_addr, (struct sockaddr *) &test.dst_in);
	if (ret)
		return ret;

	printf("mckey: joining\n");
	for (i = 0; i < connections; i++) {
		if (src_addr) {
			ret = rdma_bind_addr(test.nodes[i].cma_id,
					     test.src_addr);
			if (ret) {
				perror("mckey: addr bind failure");
				connect_error();
				return ret;
			}
		}

		if (unmapped_addr)
			ret = addr_handler(&test.nodes[i]);
		else
			ret = rdma_resolve_addr(test.nodes[i].cma_id,
						test.src_addr, test.dst_addr,
						2000);
		if (ret) {
			perror("mckey: resolve addr failure");
			connect_error();
			return ret;
		}
	}

	ret = connect_events();
	if (ret)
		goto out;

	pthread_create(&test.cmathread, NULL, cma_thread, NULL);

	/*
	 * Pause to give SM chance to configure switches.  We don't want to
	 * handle reliability issue in this simple test program.
	 */
	sleep(3);

	if (message_count) {
		if (is_sender) {
			printf("initiating data transfers\n");
			for (i = 0; i < connections; i++) {
				ret = post_sends(&test.nodes[i], 0);
				if (ret)
					goto out;
			}
		} else {
			printf("receiving data transfers\n");
			ret = poll_cqs();
			if (ret)
				goto out;
		}
		printf("data transfers complete\n");
	}
out:
	for (i = 0; i < connections; i++) {
		err = rdma_leave_multicast(test.nodes[i].cma_id,
					   test.dst_addr);
		if (err) {
			perror("mckey: failure leaving");
			ret = err;
		}
	}
	return ret;
}