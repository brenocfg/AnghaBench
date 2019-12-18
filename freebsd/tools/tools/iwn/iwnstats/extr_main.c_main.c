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
struct iwnstats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_DEFAULT_IF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ iwn_collect (struct iwnstats*) ; 
 int /*<<< orphan*/  iwn_print (struct iwnstats*) ; 
 struct iwnstats* iwnstats_new (char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  usleep (int) ; 

int
main(int argc, char *argv[])
{
	struct iwnstats *is;
	int ch;
	char *ifname;
	bool first;
	char *sysctlname;
	size_t len;
	int ret;

	ifname = strdup(IWN_DEFAULT_IF);

	/* Parse command line arguments */
	while ((ch = getopt(argc, argv,
	    "hi:")) != -1) {
		switch (ch) {
		case 'i':
			if (ifname)
				free(ifname);
			ifname = strdup(optarg);
			break;
		default:
		case '?':
		case 'h':
			usage();
			exit(1);
		}
	}

	is = iwnstats_new(ifname);

	if (is == NULL) {
		fprintf(stderr, "%s: couldn't allocate new stats structure\n",
		    argv[0]);
		exit(127);
	}

	/* begin fetching data */
	first = true;
	while (1) {
		if (iwn_collect(is) != 0) {
			fprintf(stderr, "%s: fetch failed\n", argv[0]);
			if (first)
				return 1;
			goto next;
		}

		iwn_print(is);

	next:
		usleep(100 * 1000);
		first = false;
	}

	exit(0);
}