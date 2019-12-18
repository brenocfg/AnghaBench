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
 int do_hci_command (char*,int,char**) ; 
 int getopt (int,char**,char*) ; 
 int numeric_bdaddr ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 

int
main(int argc, char *argv[])
{
	char	*node = NULL;
	int	 n;

	/* Process command line arguments */
	while ((n = getopt(argc, argv, "n:Nvh")) != -1) {
		switch (n) {
		case 'n':
			node = optarg;
			break;

		case 'N':
			numeric_bdaddr = 1;
			break;

		case 'v':
			verbose = 1;
			break;

		case 'h':
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		usage();

	n = do_hci_command(node, argc, argv);

	return (n);
}