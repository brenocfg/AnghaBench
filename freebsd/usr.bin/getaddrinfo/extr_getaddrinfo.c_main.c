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
struct addrinfo {int ai_flags; char* ai_canonname; scalar_t__ ai_protocol; scalar_t__ ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int AI_CANONNAME ; 
 int AI_NUMERICHOST ; 
 int AI_NUMERICSERV ; 
 int AI_PASSIVE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parse_af (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_protocol (char*,scalar_t__*) ; 
 int /*<<< orphan*/  parse_socktype (char*,scalar_t__*) ; 
 int /*<<< orphan*/  printaddrinfo (struct addrinfo*) ; 
 scalar_t__ printf (char*,char*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char **argv)
{
	static const struct addrinfo zero_addrinfo;
	struct addrinfo hints = zero_addrinfo;
	struct addrinfo *addrinfo;
	const char *hostname = NULL, *service = NULL;
	int ch;
	int error;

	setprogname(argv[0]);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = 0;
	hints.ai_protocol = 0;
	hints.ai_flags = 0;

	while ((ch = getopt(argc, argv, "cf:nNp:Ps:t:")) != -1) {
		switch (ch) {
		case 'c':
			hints.ai_flags |= AI_CANONNAME;
			break;

		case 'f':
			if (!parse_af(optarg, &hints.ai_family)) {
				warnx("invalid address family: %s", optarg);
				usage();
			}
			break;

		case 'n':
			hints.ai_flags |= AI_NUMERICHOST;
			break;

		case 'N':
			hints.ai_flags |= AI_NUMERICSERV;
			break;

		case 's':
			service = optarg;
			break;

		case 'p':
			if (!parse_protocol(optarg, &hints.ai_protocol)) {
				warnx("invalid protocol: %s", optarg);
				usage();
			}
			break;

		case 'P':
			hints.ai_flags |= AI_PASSIVE;
			break;

		case 't':
			if (!parse_socktype(optarg, &hints.ai_socktype)) {
				warnx("invalid socket type: %s", optarg);
				usage();
			}
			break;

		case '?':
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (!((argc == 1) || ((argc == 0) && (hints.ai_flags & AI_PASSIVE))))
		usage();
	if (argc == 1)
		hostname = argv[0];

	if (service != NULL) {
		char *p;

		if ((p = strchr(service, '/')) != NULL) {
			if (hints.ai_protocol != 0) {
				warnx("protocol already specified");
				usage();
			}
			*p = '\0';
			p++;

			if (!parse_protocol(p, &hints.ai_protocol)) {
				warnx("invalid protocol: %s", p);
				usage();
			}
		}
	}

	error = getaddrinfo(hostname, service, &hints, &addrinfo);
	if (error)
		errx(1, "%s", gai_strerror(error));

	if ((hints.ai_flags & AI_CANONNAME) && (addrinfo != NULL)) {
		if (printf("canonname %s\n", addrinfo->ai_canonname) < 0)
			err(1, "printf");
	}

	printaddrinfo(addrinfo);

	freeaddrinfo(addrinfo);

	return 0;
}