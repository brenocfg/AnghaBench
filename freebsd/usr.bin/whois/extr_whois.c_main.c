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
 char* ABUSEHOST ; 
 char* ANICHOST ; 
 char* FNICHOST ; 
 char* GNICHOST ; 
 char* IANAHOST ; 
 char* INICHOST ; 
 char* KNICHOST ; 
 char* LNICHOST ; 
 char* MNICHOST ; 
 char* PDBHOST ; 
 char* PNICHOST ; 
 int /*<<< orphan*/  QNICHOST_TAIL ; 
 char* RNICHOST ; 
 int /*<<< orphan*/  SOCKSinit (char*) ; 
 int WHOIS_QUICK ; 
 int WHOIS_RECURSE ; 
 int WHOIS_SPAM_ME ; 
 char const* choose_server (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 void* port ; 
 int /*<<< orphan*/  reset_rir () ; 
 int /*<<< orphan*/  s_asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  whois (char*,char const*,int) ; 

int
main(int argc, char *argv[])
{
	const char *country, *host;
	int ch, flags;

#ifdef	SOCKS
	SOCKSinit(argv[0]);
#endif

	country = host = NULL;
	flags = 0;
	while ((ch = getopt(argc, argv, "aAbc:fgh:iIklmp:PQrRS")) != -1) {
		switch (ch) {
		case 'a':
			host = ANICHOST;
			break;
		case 'A':
			host = PNICHOST;
			break;
		case 'b':
			host = ABUSEHOST;
			break;
		case 'c':
			country = optarg;
			break;
		case 'f':
			host = FNICHOST;
			break;
		case 'g':
			host = GNICHOST;
			break;
		case 'h':
			host = optarg;
			break;
		case 'i':
			host = INICHOST;
			break;
		case 'I':
			host = IANAHOST;
			break;
		case 'k':
			host = KNICHOST;
			break;
		case 'l':
			host = LNICHOST;
			break;
		case 'm':
			host = MNICHOST;
			break;
		case 'p':
			port = optarg;
			break;
		case 'P':
			host = PDBHOST;
			break;
		case 'Q':
			flags |= WHOIS_QUICK;
			break;
		case 'r':
			host = RNICHOST;
			break;
		case 'R':
			flags |= WHOIS_RECURSE;
			break;
		case 'S':
			flags |= WHOIS_SPAM_ME;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (!argc || (country != NULL && host != NULL))
		usage();

	/*
	 * If no host or country is specified, rely on referrals from IANA.
	 */
	if (host == NULL && country == NULL) {
		if ((host = getenv("WHOIS_SERVER")) == NULL &&
		    (host = getenv("RA_SERVER")) == NULL) {
			if (!(flags & WHOIS_QUICK))
				flags |= WHOIS_RECURSE;
		}
	}
	while (argc-- > 0) {
		if (country != NULL) {
			char *qnichost;
			s_asprintf(&qnichost, "%s%s", country, QNICHOST_TAIL);
			whois(*argv, qnichost, flags);
			free(qnichost);
		} else
			whois(*argv, host != NULL ? host :
			      choose_server(*argv), flags);
		reset_rir();
		argv++;
	}
	exit(0);
}