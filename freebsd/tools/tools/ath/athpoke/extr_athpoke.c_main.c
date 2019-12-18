#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dumpreg {scalar_t__ addr; } ;
struct ath_diag {char* ad_name; int ad_out_size; scalar_t__ ad_out_data; int /*<<< orphan*/  ad_id; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  revs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  HAL_DIAG_REVS ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ath_diag*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 struct dumpreg* reglookup (char*) ; 
 int regread (int,struct ath_diag*,scalar_t__) ; 
 int /*<<< orphan*/  regwrite (int,struct ath_diag*,scalar_t__,scalar_t__) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ state ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct ath_diag atd;
	const char *ifname;
	char *eptr;
	int c, s;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		err(1, "socket");
	ifname = getenv("ATH");
	if (!ifname)
		ifname = ATH_DEFAULT;

	while ((c = getopt(argc, argv, "i:")) != -1)
		switch (c) {
		case 'i':
			ifname = optarg;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	strncpy(atd.ad_name, ifname, sizeof (atd.ad_name));

	atd.ad_id = HAL_DIAG_REVS;
	atd.ad_out_data = (caddr_t) &state.revs;
	atd.ad_out_size = sizeof(state.revs);
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, atd.ad_name);

	argc -= optind;
	argv += optind;

	for (; argc > 0; argc--, argv++) {
		char *cp;
		const struct dumpreg *dr;
		uint32_t reg;

		cp = strchr(argv[0], '=');
		if (cp != NULL)
			*cp++ = '\0';
		dr = reglookup(argv[0]);
		if (dr == NULL) {
			errno = 0;
			reg = (uint32_t) strtoul(argv[0], &eptr, 0);
			if (argv[0] == eptr || eptr[0] != '\0')
				errx(1, "invalid register \"%s\"", argv[0]);
		} else
			reg = dr->addr;
		if (cp != NULL)
			regwrite(s, &atd, reg, (uint32_t) strtoul(cp, NULL, 0));
		printf("%s = %08x\n", argv[0], regread(s, &atd, reg));
	}
	return 0;
}