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
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  action_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDWR ; 
 uintptr_t PCI_ROM_RESERVED_MASK ; 
 int /*<<< orphan*/  PRINT ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  banner () ; 
 uintptr_t base_addr ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pci_enum_devs (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strtoumax (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int		 pci_fd;
	int		 err;
	int		 ch;
	action_t	 action;
	char		*base_addr_string;
	char		*ep;

	err = -1;
	pci_fd = -1;
	action = PRINT;
	base_addr_string = NULL;
	ep = NULL;
	progname = basename(argv[0]);

	while ((ch = getopt(argc, argv, "sb:h")) != -1)
		switch (ch) {
		case 's':
			action = SAVE;
			break;
		case 'b':
			base_addr_string = optarg;
			break;
		case 'h':
		default:
		     usage();
	}
	argc -= optind;
	argv += optind;

	if (base_addr_string != NULL) {
		uintmax_t base_addr_max;

		base_addr_max = strtoumax(base_addr_string, &ep, 16);
		if (*ep != '\0') {
			fprintf(stderr, "Invalid base address.\r\n");
			usage();
		}
		/* XXX: TODO: deal with 64-bit PCI. */
		base_addr = (uintptr_t)base_addr_max;
		base_addr &= ~PCI_ROM_RESERVED_MASK;
	}

	if (argc > 0)
		usage();

	if ((pci_fd = open(_PATH_DEVPCI, O_RDWR)) == -1) {
		perror("open");
		goto cleanup;
	}

	banner();
	pci_enum_devs(pci_fd, action);

	err = 0;
cleanup:
	if (pci_fd != -1)
		close(pci_fd);

	exit ((err == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}