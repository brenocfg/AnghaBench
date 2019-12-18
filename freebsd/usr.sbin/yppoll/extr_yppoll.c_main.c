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
typedef  int time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctime (int*) ; 
 int /*<<< orphan*/  errx (int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int get_remote_info (char*,char*,char*,int*,char**) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  yp_get_default_domain (char**) ; 
 int yp_master (char*,char*,char**) ; 
 int yp_order (char*,char*,int*) ; 
 int /*<<< orphan*/  yperr_string (int) ; 

int
main(int argc, char *argv[])
{
	char *domainname, *hostname = NULL, *inmap, *master;
	int order, c, r;
	time_t torder;

	yp_get_default_domain(&domainname);

	while ((c = getopt(argc, argv, "h:d:")) != -1)
		switch (c) {
		case 'd':
			domainname = optarg;
			break;
		case 'h':
			hostname = optarg;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}

	if (optind + 1 != argc)
		usage();
	inmap = argv[optind];

	if (hostname != NULL) {
		r = get_remote_info(domainname, inmap, hostname,
		    &order, &master);
	} else {
		r = yp_order(domainname, inmap, &order);
		if (r == 0)
			r = yp_master(domainname, inmap, &master);
	}

	if (r != 0)
		errx(1, "no such map %s: reason: %s",
		    inmap, yperr_string(r));

	torder = order;
	printf("Map %s has order number %lld. %s", inmap,
	    (long long)order, ctime(&torder));
	printf("The master server is %s.\n", master);

	exit(0);
}