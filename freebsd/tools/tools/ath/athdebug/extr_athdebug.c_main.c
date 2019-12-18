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
typedef  int uint64_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  oid ;
typedef  int /*<<< orphan*/  ndebug ;
typedef  int /*<<< orphan*/  debug ;
struct TYPE_3__ {int bit; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 TYPE_1__* flags ; 
 char* getenv (char*) ; 
 int getflag (char const*,int) ; 
 scalar_t__ isdigit (char const) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const char *ifname;
	const char *cp, *tp;
	const char *sep;
	int c, op, i;
	uint64_t debug, ndebug;
	size_t debuglen;
	char oid[256];

	ifname = getenv("ATH");
	if (ifname == NULL)
		ifname = ATH_DEFAULT;
	progname = argv[0];
	if (argc > 1) {
		if (strcmp(argv[1], "-i") == 0) {
			if (argc < 2)
				errx(1, "missing interface name for -i option");
			ifname = argv[2];
			if (strncmp(ifname, "ath", 3) != 0)
				errx(2, "huh, this is for ath devices?");
			argc -= 2, argv += 2;
		} else if (strcmp(argv[1], "-?") == 0)
			usage();
	}

#ifdef __linux__
	snprintf(oid, sizeof(oid), "dev.%s.debug", ifname);
#else
	snprintf(oid, sizeof(oid), "dev.ath.%s.debug", ifname+3);
#endif
	debuglen = sizeof(debug);
	if (sysctlbyname(oid, &debug, &debuglen, NULL, 0) < 0)
		err(1, "sysctl-get(%s)", oid);
	ndebug = debug;
	for (; argc > 1; argc--, argv++) {
		cp = argv[1];
		do {
			u_int bit;

			if (*cp == '-') {
				cp++;
				op = -1;
			} else if (*cp == '+') {
				cp++;
				op = 1;
			} else
				op = 0;
			for (tp = cp; *tp != '\0' && *tp != '+' && *tp != '-';)
				tp++;
			bit = getflag(cp, tp-cp);
			if (op < 0)
				ndebug &= ~bit;
			else if (op > 0)
				ndebug |= bit;
			else {
				if (bit == 0) {
					if (isdigit(*cp))
						bit = strtoul(cp, NULL, 0);
					else
						errx(1, "unknown flag %.*s",
							(int) (tp-cp), cp);
				}
				ndebug = bit;
			}
		} while (*(cp = tp) != '\0');
	}
	if (debug != ndebug) {
		printf("%s: 0x%llx => ", oid, (long long) debug);
		if (sysctlbyname(oid, NULL, NULL, &ndebug, sizeof(ndebug)) < 0)
			err(1, "sysctl-set(%s)", oid);
		printf("0x%llx", (long long) ndebug);
		debug = ndebug;
	} else
		printf("%s: 0x%llx", oid, (long long) debug);
	sep = "<";
	for (i = 0; i < nitems(flags); i++)
		if (debug & flags[i].bit) {
			printf("%s%s", sep, flags[i].name);
			sep = ",";
		}
	printf("%s\n", *sep != '<' ? ">" : "");
	return 0;
}