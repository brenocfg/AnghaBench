#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long timeout; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  secret; int /*<<< orphan*/  name; void* proto; } ;
struct TYPE_6__ {int /*<<< orphan*/  secret; int /*<<< orphan*/  name; void* proto; } ;
struct TYPE_8__ {int enable_vj; int enable_ipv6; TYPE_1__ lcp; TYPE_3__ hisauth; TYPE_2__ myauth; } ;
struct spppreq {uintptr_t cmd; TYPE_4__ defs; } ;
struct ifreq {scalar_t__ ifr_data; int /*<<< orphan*/  ifr_name; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AUTHFLAG_NOCALLOUT ; 
 int /*<<< orphan*/  AUTHFLAG_NORECHALLENGE ; 
 int AUTHKEYLEN ; 
 int AUTHNAMELEN ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 void* PPP_CHAP ; 
 void* PPP_PAP ; 
 int /*<<< orphan*/  SIOCGIFGENERIC ; 
 int /*<<< orphan*/  SIOCSIFGENERIC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ SPPPIOGDEFS ; 
 scalar_t__ SPPPIOSDEFS ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_vals (char const*,struct spppreq*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ startswith (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 long strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int s, c;
	int errs = 0, verbose = 0;
	size_t off;
	long to;
	char *endp;
	const char *ifname, *cp;
	struct ifreq ifr;
	struct spppreq spr;

	while ((c = getopt(argc, argv, "v")) != -1)
		switch (c) {
		case 'v':
			verbose++;
			break;

		default:
			errs++;
			break;
		}
	argv += optind;
	argc -= optind;

	if (errs || argc < 1)
		usage();

	ifname = argv[0];
	strncpy(ifr.ifr_name, ifname, sizeof ifr.ifr_name);

	/* use a random AF to create the socket */
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err(EX_UNAVAILABLE, "ifconfig: socket");

	argc--;
	argv++;

	spr.cmd = (uintptr_t) SPPPIOGDEFS;
	ifr.ifr_data = (caddr_t)&spr;

	if (ioctl(s, SIOCGIFGENERIC, &ifr) == -1)
		err(EX_OSERR, "SIOCGIFGENERIC(SPPPIOGDEFS)");

	if (argc == 0) {
		/* list only mode */
		print_vals(ifname, &spr);
		return 0;
	}

#define startswith(s) strncmp(argv[0], s, (off = strlen(s))) == 0

	while (argc > 0) {
		if (startswith("authproto=")) {
			cp = argv[0] + off;
			if (strcmp(cp, "pap") == 0)
				spr.defs.myauth.proto =
					spr.defs.hisauth.proto = PPP_PAP;
			else if (strcmp(cp, "chap") == 0)
				spr.defs.myauth.proto =
					spr.defs.hisauth.proto = PPP_CHAP;
			else if (strcmp(cp, "none") == 0)
				spr.defs.myauth.proto =
					spr.defs.hisauth.proto = 0;
			else
				errx(EX_DATAERR, "bad auth proto: %s", cp);
		} else if (startswith("myauthproto=")) {
			cp = argv[0] + off;
			if (strcmp(cp, "pap") == 0)
				spr.defs.myauth.proto = PPP_PAP;
			else if (strcmp(cp, "chap") == 0)
				spr.defs.myauth.proto = PPP_CHAP;
			else if (strcmp(cp, "none") == 0)
				spr.defs.myauth.proto = 0;
			else
				errx(EX_DATAERR, "bad auth proto: %s", cp);
		} else if (startswith("myauthname="))
			strncpy(spr.defs.myauth.name, argv[0] + off,
				AUTHNAMELEN);
		else if (startswith("myauthsecret=") ||
			 startswith("myauthkey="))
			strncpy(spr.defs.myauth.secret, argv[0] + off,
				AUTHKEYLEN);
		else if (startswith("hisauthproto=")) {
			cp = argv[0] + off;
			if (strcmp(cp, "pap") == 0)
				spr.defs.hisauth.proto = PPP_PAP;
			else if (strcmp(cp, "chap") == 0)
				spr.defs.hisauth.proto = PPP_CHAP;
			else if (strcmp(cp, "none") == 0)
				spr.defs.hisauth.proto = 0;
			else
				errx(EX_DATAERR, "bad auth proto: %s", cp);
		} else if (startswith("hisauthname="))
			strncpy(spr.defs.hisauth.name, argv[0] + off,
				AUTHNAMELEN);
		else if (startswith("hisauthsecret=") ||
			 startswith("hisauthkey="))
			strncpy(spr.defs.hisauth.secret, argv[0] + off,
				AUTHKEYLEN);
		else if (strcmp(argv[0], "callin") == 0)
			spr.defs.hisauth.flags |= AUTHFLAG_NOCALLOUT;
		else if (strcmp(argv[0], "always") == 0)
			spr.defs.hisauth.flags &= ~AUTHFLAG_NOCALLOUT;
		else if (strcmp(argv[0], "norechallenge") == 0)
			spr.defs.hisauth.flags |= AUTHFLAG_NORECHALLENGE;
		else if (strcmp(argv[0], "rechallenge") == 0)
			spr.defs.hisauth.flags &= ~AUTHFLAG_NORECHALLENGE;
		else if (startswith("lcp-timeout=")) {
			cp = argv[0] + off;
			to = strtol(cp, &endp, 10);
			if (*cp == '\0' || *endp != '\0' ||
			    /*
			     * NB: 10 ms is the minimal possible value for
			     * hz=100.  We assume no kernel has less clock
			     * frequency than that...
			     */
			    to < 10 || to > 20000)
				errx(EX_DATAERR, "bad lcp timeout value: %s",
				     cp);
			spr.defs.lcp.timeout = to;
		} else if (strcmp(argv[0], "enable-vj") == 0)
			spr.defs.enable_vj = 1;
		else if (strcmp(argv[0], "disable-vj") == 0)
			spr.defs.enable_vj = 0;
		else if (strcmp(argv[0], "enable-ipv6") == 0)
			spr.defs.enable_ipv6 = 1;
		else if (strcmp(argv[0], "disable-ipv6") == 0)
			spr.defs.enable_ipv6 = 0;
		else
			errx(EX_DATAERR, "bad parameter: \"%s\"", argv[0]);

		argv++;
		argc--;
	}

	spr.cmd = (uintptr_t)SPPPIOSDEFS;

	if (ioctl(s, SIOCSIFGENERIC, &ifr) == -1)
		err(EX_OSERR, "SIOCSIFGENERIC(SPPPIOSDEFS)");

	if (verbose)
		print_vals(ifname, &spr);

	return 0;
}