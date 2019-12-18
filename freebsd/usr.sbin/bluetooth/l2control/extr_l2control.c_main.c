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
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  bdaddr ;

/* Variables and functions */
 int /*<<< orphan*/  bt_aton (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (int /*<<< orphan*/ ) ; 
 int do_l2cap_command (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numeric_bdaddr ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int		n;
	bdaddr_t	bdaddr;

	memset(&bdaddr, 0, sizeof(bdaddr));

	/* Process command line arguments */
	while ((n = getopt(argc, argv, "a:nh")) != -1) {
		switch (n) {
		case 'a':
			if (!bt_aton(optarg, &bdaddr)) {
				struct hostent	*he = NULL;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));

				memcpy(&bdaddr, he->h_addr, sizeof(bdaddr));
			}
			break;

		case 'n':
			numeric_bdaddr = 1;
			break;

		case 'h':
		default:
			usage();
			break;
		}
	}

	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		usage();

	return (do_l2cap_command(&bdaddr, argc, argv));
}