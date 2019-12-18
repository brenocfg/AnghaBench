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
struct link {int op; void* id2; void* id1; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 void* atoi (char const*) ; 
 scalar_t__ dev ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  link_op (struct link*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  toggle_medium (int) ; 
 int /*<<< orphan*/  usage (char const**) ; 

int
main(int argc, const char* argv[])
{
	struct link l;
	char cmd;

	if (argc < 2) {
		usage(argv);
		exit(1);
	}

	dev = open("/dev/visctl", O_RDONLY);
		if (dev < 0) {
			printf("error opening visctl cdev\n");
			exit(1);
	}

	cmd = (char)*argv[1];

	switch (cmd) {
	case 'o':
		toggle_medium(1);
		break;
	case 'c':
		toggle_medium(0);
		break;
	case 'a':
		if (argc < 4) {
			usage(argv);
			exit(1);
		}
		l.op = 1;
		l.id1 = atoi(argv[2]);
		l.id2 = atoi(argv[3]);
		link_op(&l);
		break;
	case 'd':
		if (argc < 4) {
			usage(argv);
			exit(1);
		}
		l.op = 0;
		l.id1 = atoi(argv[2]);
		l.id2 = atoi(argv[3]);
		link_op(&l);
		break;
	default:
		printf("wtap ioctl: unknown command '%c'\n", *argv[1]);
		exit(1);
	}
	exit(0);
}