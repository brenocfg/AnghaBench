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
struct TYPE_2__ {scalar_t__ option; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int TEST_CNT ; 
 int /*<<< orphan*/  buf ; 
 int client_connect () ; 
 int /*<<< orphan*/  custom ; 
 scalar_t__ dst_addr ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_bandwidth_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_latency_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_bandwidth ; 
 int /*<<< orphan*/  opt_latency ; 
 int /*<<< orphan*/  optimization ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  rshutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_test () ; 
 int server_connect () ; 
 int server_listen () ; 
 scalar_t__ size_option ; 
 TYPE_1__* test_size ; 
 int /*<<< orphan*/  transfer_size ; 

__attribute__((used)) static int run(void)
{
	int i, ret = 0;

	buf = malloc(!custom ? test_size[TEST_CNT - 1].size : transfer_size);
	if (!buf) {
		perror("malloc");
		return -1;
	}

	if (!dst_addr) {
		ret = server_listen();
		if (ret)
			goto free;
	}

	printf("%-10s%-8s%-8s%-8s%-8s%8s %10s%13s\n",
	       "name", "bytes", "xfers", "iters", "total", "time", "Gb/sec", "usec/xfer");
	if (!custom) {
		optimization = opt_latency;
		ret = dst_addr ? client_connect() : server_connect();
		if (ret)
			goto free;

		for (i = 0; i < TEST_CNT; i++) {
			if (test_size[i].option > size_option)
				continue;
			init_latency_test(test_size[i].size);
			run_test();
		}
		rshutdown(rs, SHUT_RDWR);
		rclose(rs);

		optimization = opt_bandwidth;
		ret = dst_addr ? client_connect() : server_connect();
		if (ret)
			goto free;
		for (i = 0; i < TEST_CNT; i++) {
			if (test_size[i].option > size_option)
				continue;
			init_bandwidth_test(test_size[i].size);
			run_test();
		}
	} else {
		ret = dst_addr ? client_connect() : server_connect();
		if (ret)
			goto free;

		ret = run_test();
	}

	rshutdown(rs, SHUT_RDWR);
	rclose(rs);
free:
	free(buf);
	return ret;
}