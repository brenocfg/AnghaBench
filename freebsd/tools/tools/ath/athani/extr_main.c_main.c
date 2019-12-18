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
struct ath_driver_req {int dummy; } ;
struct ath_diag {int dummy; } ;

/* Variables and functions */
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  ani_read_state (struct ath_driver_req*,char const*) ; 
 scalar_t__ ani_write_state (struct ath_driver_req*,char const*,char*,char*) ; 
 int /*<<< orphan*/  ath_driver_req_init (struct ath_driver_req*) ; 
 scalar_t__ ath_driver_req_open (struct ath_driver_req*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  list_labels () ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct ath_diag atd;
	const char *ifname;
	struct ath_driver_req req;
	int what, c;

	ath_driver_req_init(&req);

	ifname = getenv("ATH");
	if (!ifname)
		ifname = ATH_DEFAULT;

	what = 0;
	while ((c = getopt(argc, argv, "i:l")) != -1)
		switch (c) {
		case 'i':
			ifname = optarg;
			break;
		case 'l':
			list_labels();
			exit(0);
		default:
			usage();
			/*NOTREACHED*/
		}

	/* Initialise the driver interface */
	if (ath_driver_req_open(&req, ifname) < 0) {
		exit(127);
	}

	argc -= optind;
	argv += optind;

	if (argc == 0) {
		ani_read_state(&req, ifname);
		exit(0);
	}

	if (argc < 2) {
		usage();
		/*NOTREACHED*/
	}

	if (ani_write_state(&req, ifname, argv[0], argv[1]) != 0)
		exit(1);

	exit(0);
}