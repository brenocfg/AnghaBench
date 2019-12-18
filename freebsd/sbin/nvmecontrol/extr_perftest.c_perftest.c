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
typedef  int /*<<< orphan*/  u_long ;
struct nvme_io_test {int num_threads; scalar_t__ time; int /*<<< orphan*/  size; int /*<<< orphan*/  opc; int /*<<< orphan*/  flags; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  io_test ;
struct TYPE_2__ {char* op; char* flags; char* intr; int threads; scalar_t__ time; int /*<<< orphan*/  perthread; int /*<<< orphan*/  dev; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_BIO_TEST ; 
 int /*<<< orphan*/  NVME_IO_TEST ; 
 int /*<<< orphan*/  NVME_OPC_READ ; 
 int /*<<< orphan*/  NVME_OPC_WRITE ; 
 int /*<<< orphan*/  NVME_TEST_FLAG_REFTHREAD ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_io_test*) ; 
 int /*<<< orphan*/  memset (struct nvme_io_test*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 TYPE_1__ opt ; 
 int /*<<< orphan*/  print_perftest (struct nvme_io_test*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
perftest(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_io_test		io_test;
	int				fd;
	u_long				ioctl_cmd = NVME_IO_TEST;

	memset(&io_test, 0, sizeof(io_test));
	if (arg_parse(argc, argv, f))
		return;
	
	if (opt.op == NULL)
		arg_help(argc, argv, f);
	if (opt.flags != NULL && strcmp(opt.flags, "refthread") == 0)
		io_test.flags |= NVME_TEST_FLAG_REFTHREAD;
	if (opt.intr != NULL) {
		if (strcmp(opt.intr, "bio") == 0 ||
		    strcmp(opt.intr, "wait") == 0)
			ioctl_cmd = NVME_BIO_TEST;
		else if (strcmp(opt.intr, "io") == 0 ||
		    strcmp(opt.intr, "intr") == 0)
			ioctl_cmd = NVME_IO_TEST;
		else {
			fprintf(stderr, "Unknown interrupt test type %s\n", opt.intr);
			arg_help(argc, argv, f);
		}
	}
	if (opt.threads <= 0 || opt.threads > 128) {
		fprintf(stderr, "Bad number of threads %d\n", opt.threads);
		arg_help(argc, argv, f);
	}
	io_test.num_threads = opt.threads;
	if (strcasecmp(opt.op, "read") == 0)
		io_test.opc = NVME_OPC_READ;
	else if (strcasecmp(opt.op, "write") == 0)
		io_test.opc = NVME_OPC_WRITE;
	else {
		fprintf(stderr, "\"%s\" not valid opcode.\n", opt.op);
		arg_help(argc, argv, f);
	}
	if (opt.time == 0) {
		fprintf(stderr, "No time speciifed\n");
		arg_help(argc, argv, f);
	}
	io_test.time = opt.time;
	io_test.size = opt.size;
	open_dev(opt.dev, &fd, 1, 1);
	if (ioctl(fd, ioctl_cmd, &io_test) < 0)
		err(1, "ioctl NVME_IO_TEST failed");

	close(fd);
	print_perftest(&io_test, opt.perthread);
	exit(0);
}