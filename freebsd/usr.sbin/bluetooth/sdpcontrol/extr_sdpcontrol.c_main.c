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
 char* SDP_LOCAL_PATH ; 
 int /*<<< orphan*/  bt_aton (char*,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (char*) ; 
 int do_sdp_command (int /*<<< orphan*/ *,char const*,int,int,char**) ; 
 int /*<<< orphan*/  errx (int,char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char const	*control = SDP_LOCAL_PATH;
	int		 n, local;
	bdaddr_t	 bdaddr;

	memset(&bdaddr, 0, sizeof(bdaddr));
	local = 0;

	/* Process command line arguments */
	while ((n = getopt(argc, argv, "a:c:lh")) != -1) {
		switch (n) {
		case 'a': /* bdaddr */
			if (!bt_aton(optarg, &bdaddr)) {
				struct hostent  *he = NULL;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));
 
				memcpy(&bdaddr, he->h_addr, sizeof(bdaddr));
			}
			break;

		case 'c': /* control socket */
			control = optarg;
			break;

		case 'l': /* local sdpd */
			local = 1;
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

	return (do_sdp_command(&bdaddr, control, local, argc, argv));
}