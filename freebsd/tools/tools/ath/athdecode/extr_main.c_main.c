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
struct stat {int st_size; } ;
struct athregrec {int op; } ;
struct TYPE_2__ {int chipnum; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_PRIVATE ; 
#define  OP_DEVICE 131 
#define  OP_MARK 130 
#define  OP_READ 129 
#define  OP_WRITE 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ bcmp (struct athregrec*,struct athregrec*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 void* mmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opdevice (struct athregrec*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opmark (int /*<<< orphan*/ ,int,struct athregrec*) ; 
 int /*<<< orphan*/  oprw (int /*<<< orphan*/ ,int,struct athregrec*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char *argv[])
{
	int fd, i, nrecs, same;
	struct stat sb;
	void *addr;
	const char *filename = "/tmp/ath_hal.log";
	struct athregrec *rprev;

	if (argc > 1)
		filename = argv[1];
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err(1, "open: %s", filename);
	if (fstat(fd, &sb) < 0)
		err(1, "fstat");
	addr = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE|MAP_NOCORE, fd, 0);
	if (addr == MAP_FAILED)
		err(1, "mmap");
	nrecs = sb.st_size / sizeof (struct athregrec);
	printf("%u records", nrecs);
	rprev = NULL;
	same = 0;
	state.chipnum = 5210;
	for (i = 0; i < nrecs; i++) {
		struct athregrec *r = &((struct athregrec *) addr)[i];
		if (rprev && bcmp(r, rprev, sizeof (*r)) == 0) {
			same++;
			continue;
		}
		if (same)
			printf("\t\t+%u time%s", same, same == 1 ? "" : "s");
		switch (r->op) {
		case OP_DEVICE:
			opdevice(r);
			break;
		case OP_READ:
		case OP_WRITE:
			oprw(stdout, i, r);
			break;
		case OP_MARK:
			opmark(stdout, i, r);
			break;
		}
		rprev = r;
		same = 0;
	}
	putchar('\n');
	return 0;
}