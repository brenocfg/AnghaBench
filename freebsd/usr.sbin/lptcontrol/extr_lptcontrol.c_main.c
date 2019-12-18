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
 char* DEFAULT_DEVICE ; 
 int DO_POLL ; 
 int IRQ_UNSPECIFIED ; 
 int /*<<< orphan*/  LPT_IRQ ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int USE_EXT_MODE ; 
 int USE_IRQ ; 
 int USE_STD_MODE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int main (int argc, char **argv)
{
	const char *device;
	int fd;
	int irq_status;
	int opt;

	device = DEFAULT_DEVICE;
	irq_status = IRQ_UNSPECIFIED;
	while ((opt = getopt(argc, argv, "d:eips")) != -1)
		switch (opt) {
		case 'd':
			device = optarg;
			break;
		case 'e':
			irq_status = USE_EXT_MODE;
			break;
		case 'i':
			irq_status = USE_IRQ;
			break;
		case 'p':
			irq_status = DO_POLL;
			break;
		case 's':
			irq_status = USE_STD_MODE;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	argc -= optind;
	argv += optind;
	/* POLA: DTRT if -d was forgotten, but device name was specified. */
	if (argc == 1) {
		device = argv[0];
		--argc;
	}

	if (irq_status == IRQ_UNSPECIFIED || argc != 0)
		usage();

	if ((fd = open(device, O_WRONLY)) < 0)
		err(1, "open");
	if (ioctl(fd, LPT_IRQ, &irq_status) < 0)
		err(1, "ioctl");
	close(fd);

	return(0);
}