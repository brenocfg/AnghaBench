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
typedef  int u_int ;
struct test_func {int (* func ) () ;int /*<<< orphan*/  desc; } ;
struct TYPE_2__ {int sock_type; char* sock_type_str; } ;

/* Variables and functions */
 int SOCK_STREAM ; 
 int TEST_DGRAM_TBL_SIZE ; 
 int TEST_STREAM_TBL_SIZE ; 
 int failed_flag ; 
 int stub1 () ; 
 struct test_func* test_dgram_tbl ; 
 struct test_func* test_stream_tbl ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_logmsgx (char*) ; 
 int /*<<< orphan*/  uc_output (char*,...) ; 

__attribute__((used)) static int
run_tests(int type, u_int testno1)
{
	const struct test_func *tf;
	u_int i, testno2, failed_num;

	uc_cfg.sock_type = type;
	if (type == SOCK_STREAM) {
		uc_cfg.sock_type_str = "SOCK_STREAM";
		tf = test_stream_tbl;
		i = TEST_STREAM_TBL_SIZE - 1;
	} else {
		uc_cfg.sock_type_str = "SOCK_DGRAM";
		tf = test_dgram_tbl;
		i = TEST_DGRAM_TBL_SIZE - 1;
	}
	if (testno1 == 0) {
		testno1 = 1;
		testno2 = i;
	} else
		testno2 = testno1;

	uc_output("Running tests for %s sockets:\n", uc_cfg.sock_type_str);
	failed_num = 0;
	for (i = testno1, tf += testno1; i <= testno2; ++tf, ++i) {
		uc_output("  %u: %s\n", i, tf->desc);
		switch (tf->func()) {
		case -1:
			++failed_num;
			break;
		case -2:
			uc_logmsgx("some system error or timeout occurred");
			return (-1);
		}
	}

	if (failed_num != 0)
		failed_flag = true;

	if (testno1 != testno2) {
		if (failed_num == 0)
			uc_output("-- all tests passed!\n");
		else
			uc_output("-- %u test%s failed!\n",
			    failed_num, failed_num == 1 ? "" : "s");
	} else {
		if (failed_num == 0)
			uc_output("-- test passed!\n");
		else
			uc_output("-- test failed!\n");
	}

	return (0);
}