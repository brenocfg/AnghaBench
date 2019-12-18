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
typedef  int /*<<< orphan*/  hs ;
typedef  int /*<<< orphan*/  HAL_CHANNEL_SURVEY ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ get_survey_stats (int,char const*,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  process_survey_stats (int /*<<< orphan*/ *) ; 
 char* progname ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	FILE *fd = NULL;
	const char *ifname;
	int c, s;
	int l = 0;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		err(1, "socket");
	ifname = getenv("ATH");
	if (!ifname)
		ifname = ATH_DEFAULT;

	progname = argv[0];
	while ((c = getopt(argc, argv, "i:")) != -1)
		switch (c) {
		case 'i':
			ifname = optarg;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	argc -= optind;
	argv += optind;

	/* Now, loop over and fetch some statistics .. */
	while (1) {
		HAL_CHANNEL_SURVEY hs;
		memset(&hs, '\0', sizeof(hs));
		if (get_survey_stats(s, ifname, &hs) == 0)
			break;
		/* XXX screen height! */
		if (l % 23 == 0) {
			printf("         "
			    "min                   "
			    "avg                   "
			    "max\n");
			printf("  tx%%  rx%%  bc%%  ec%%  ");
			printf("  tx%%  rx%%  bc%%  ec%%  ");
			printf("  tx%%  rx%%  bc%%  ec%%\n");
		}
		process_survey_stats(&hs);
		sleep(1);
		l++;
	}

	return (0);
}