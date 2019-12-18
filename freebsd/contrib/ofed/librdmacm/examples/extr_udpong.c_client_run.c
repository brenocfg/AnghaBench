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
 int TEST_CNT ; 
 int client_connect () ; 
 int /*<<< orphan*/  custom ; 
 int /*<<< orphan*/  init_bandwidth_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_latency_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  rs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_test () ; 
 int /*<<< orphan*/ * test_size ; 

__attribute__((used)) static int client_run(void)
{
	int i, ret;

	printf("%-10s%-8s%-8s%-8s%8s %10s%13s\n",
	       "name", "bytes", "xfers", "total", "time", "Gb/sec", "usec/xfer");

	ret = client_connect();
	if (ret)
		return ret;

	if (!custom) {
		for (i = 0; i < TEST_CNT; i++) {
			init_latency_test(test_size[i]);
			run_test();
		}
		for (i = 0; i < TEST_CNT; i++) {
			init_bandwidth_test(test_size[i]);
			run_test();
		}
	} else {
		run_test();
	}
	rs_close(rs);

	return ret;
}