#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ bind_tohost (struct sockaddr_in*,char*,char*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct hostent* gethostbyname (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_aton (char*,TYPE_1__*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  yp_get_default_domain (char**) ; 

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	struct hostent *hent;
	char *domainname;
	int c;

	yp_get_default_domain(&domainname);

	bzero(&sin, sizeof sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	while ((c = getopt(argc, argv, "h:d:")) != -1)
		switch (c) {
		case 'd':
			domainname = optarg;
			break;
		case 'h':
			if (inet_aton(optarg, &sin.sin_addr) == 0) {
				hent = gethostbyname(optarg);
				if (hent == NULL)
					errx(1, "host %s unknown\n", optarg);
				bcopy(hent->h_addr, &sin.sin_addr,
				    sizeof(sin.sin_addr));
			}
			break;
		default:
			usage();
		}

	if (optind + 1 != argc)
		usage();

	if (bind_tohost(&sin, domainname, argv[optind]))
		exit(1);
	exit(0);
}