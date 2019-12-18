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
 int /*<<< orphan*/  NG_HCI_BDADDR_ANY ; 
 int /*<<< orphan*/  bt_aton (void*,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (void*) ; 
 void* config_file ; 
 int do_bthid_command (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  errx (int,char*,void*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hid_init (int /*<<< orphan*/ *) ; 
 void* hids_file ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbose ; 

int
main(int argc, char *argv[])
{
	bdaddr_t	bdaddr;
	int		opt;

	hid_init(NULL);
	memcpy(&bdaddr, NG_HCI_BDADDR_ANY, sizeof(bdaddr));

	while ((opt = getopt(argc, argv, "a:c:H:hv")) != -1) {
		switch (opt) {
		case 'a': /* bdaddr */
			if (!bt_aton(optarg, &bdaddr)) {
				struct hostent  *he = NULL;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));

				memcpy(&bdaddr, he->h_addr, sizeof(bdaddr));
			}
			break;

		case 'c': /* config file */
			config_file = optarg;
			break;

		case 'H': /* HIDs file */
			hids_file = optarg;
			break;

		case 'v': /* verbose */
			verbose++;
			break;

		case 'h':
		default:
			usage();
			/* NOT REACHED */
		}
	}

	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		usage();

	return (do_bthid_command(&bdaddr, argc, argv));
}