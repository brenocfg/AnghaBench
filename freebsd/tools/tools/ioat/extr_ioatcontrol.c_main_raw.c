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
struct ioat_test {int transactions; int chain_depth; int buffer_size; scalar_t__ raw_target; int /*<<< orphan*/  testkind; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IOAT_DMATEST ; 
 int /*<<< orphan*/  IOAT_TEST_RAW_DMA ; 
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct ioat_test*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prettyprint (struct ioat_test*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
main_raw(struct ioat_test *t, int argc, char **argv)
{
	int fd;

	/* Raw DMA defaults */
	t->testkind = IOAT_TEST_RAW_DMA;
	t->transactions = 1;
	t->chain_depth = 1;
	t->buffer_size = 4 * 1024;

	t->raw_target = strtoull(argv[1], NULL, 0);
	if (t->raw_target == 0) {
		printf("Target shoudln't be NULL\n");
		exit(EX_USAGE);
	}

	if (argc >= 3) {
		t->buffer_size = atoi(argv[2]);
		if (t->buffer_size == 0) {
			printf("Buffer size must be greater than zero\n");
			exit(EX_USAGE);
		}
	}

	fd = open("/dev/ioat_test", O_RDWR);
	if (fd < 0) {
		printf("Cannot open /dev/ioat_test\n");
		exit(EX_UNAVAILABLE);
	}

	(void)ioctl(fd, IOAT_DMATEST, t);
	close(fd);

	exit(prettyprint(t));
}