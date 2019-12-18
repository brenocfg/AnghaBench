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
typedef  int /*<<< orphan*/  tests ;
struct sendfile_test {int offset; int length; int file_size; int /*<<< orphan*/  hdr_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int const TEST_PAGES ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fork () ; 
 int getpagesize () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ new_test_socket (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_child () ; 
 scalar_t__ send_test (int,struct sendfile_test) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_test_file (size_t) ; 

__attribute__((used)) static void
run_parent(void)
{
	int connect_socket;
	int status;
	int test_num;
	int test_count;
	int pid;
	size_t desired_file_size = 0;

	const int pagesize = getpagesize();

	struct sendfile_test tests[] = {
 		{ .hdr_length = 0, .offset = 0, .length = 1 },
		{ .hdr_length = 0, .offset = 0, .length = pagesize },
		{ .hdr_length = 0, .offset = 1, .length = 1 },
		{ .hdr_length = 0, .offset = 1, .length = pagesize },
		{ .hdr_length = 0, .offset = pagesize, .length = pagesize },
		{ .hdr_length = 0, .offset = 0, .length = 2*pagesize },
		{ .hdr_length = 0, .offset = 0, .length = 0 },
		{ .hdr_length = 0, .offset = pagesize, .length = 0 },
		{ .hdr_length = 0, .offset = 2*pagesize, .length = 0 },
		{ .hdr_length = 0, .offset = TEST_PAGES*pagesize, .length = 0 },
		{ .hdr_length = 0, .offset = 0, .length = pagesize,
		    .file_size = 1 }
	};

	test_count = sizeof(tests) / sizeof(tests[0]);
	printf("1..%d\n", test_count);

	for (test_num = 1; test_num <= test_count; test_num++) {

		desired_file_size = tests[test_num - 1].file_size;
		if (desired_file_size == 0)
			desired_file_size = TEST_PAGES * pagesize;
		if (write_test_file(desired_file_size) != 0) {
			printf("not ok %d\n", test_num);
			continue;
		}

		pid = fork();
		if (pid == -1) {
			printf("not ok %d\n", test_num);
			continue;
		}

		if (pid == 0)
			run_child();

		usleep(250000);

		if (new_test_socket(&connect_socket) != 0) {
			printf("not ok %d\n", test_num);
			kill(pid, SIGALRM);
			close(connect_socket);
			continue;
		}

		if (send_test(connect_socket, tests[test_num-1]) != 0) {
			printf("not ok %d\n", test_num);
			kill(pid, SIGALRM);
			close(connect_socket);
			continue;
		}

		close(connect_socket);
		if (waitpid(pid, &status, 0) == pid) {
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				printf("%s %d\n", "ok", test_num);
			else
				printf("%s %d\n", "not ok", test_num);
		}
		else {
			printf("not ok %d\n", test_num);
		}
	}
}