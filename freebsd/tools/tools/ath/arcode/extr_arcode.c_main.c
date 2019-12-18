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
struct athregrec {int op; int reg; int val; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
#define  OP_DEVICE 131 
#define  OP_MARK 130 
#define  OP_READ 129 
#define  OP_WRITE 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  op_device (struct athregrec*) ; 
 int /*<<< orphan*/  op_mark (struct athregrec*) ; 
 int /*<<< orphan*/  op_read (struct athregrec*) ; 
 int /*<<< orphan*/  op_write (struct athregrec*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,struct athregrec*,int) ; 

int
main(int argc, const char *argv[])
{
	const char *file = argv[1];
	int fd;
	struct athregrec a;
	int r;

	if (argc < 2) {
		printf("usage: %s <ahq log>\n", argv[0]);
		exit(127);
	}

	fd = open(file, O_RDONLY);
	if (fd < 0) {
		perror("open"); 
		exit(127);
	}

	while (1) {
		r = read(fd, &a, sizeof(a));
		if (r != sizeof(a))
			break;
		switch (a.op) {
			case OP_READ:
				op_read(&a);
				break;
			case OP_WRITE:
				op_write(&a);
				break;
			case OP_DEVICE:
				op_device(&a);
				break;
			case OP_MARK:
				op_mark(&a);
				break;
			default:
				printf("op: %d; reg: 0x%x; val: 0x%x\n",
				    a.op, a.reg, a.val);
		}
	}
	close(fd);
}