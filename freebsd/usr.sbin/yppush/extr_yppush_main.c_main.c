#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  myname ;
struct TYPE_4__ {char* data; int size; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ YP_TRUE ; 
 int /*<<< orphan*/  _yp_check (char**) ; 
 void* atoi (void*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ gethostname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handler ; 
 char* malloc (int) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skip_master ; 
 char* strdup (void*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 void* yp_dir ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int /*<<< orphan*/  yp_get_default_domain (char**) ; 
 scalar_t__ yp_get_record (char*,char*,TYPE_1__*,TYPE_1__*,int) ; 
 char* yppush_domain ; 
 int /*<<< orphan*/  yppush_exit (int) ; 
 int /*<<< orphan*/  yppush_foreach (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int yppush_jobs ; 
 char* yppush_mapname ; 
 char* yppush_master ; 
 void* yppush_timeout ; 
 int /*<<< orphan*/  yppush_transid ; 
 int /*<<< orphan*/  ypxfr_get_map (char*,char*,char*,int /*<<< orphan*/  (*) (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 

int
main(int argc, char *argv[])
{
	int ch;
	DBT key, data;
	char myname[MAXHOSTNAMELEN];
	struct hostlist {
		char *name;
		struct hostlist *next;
	};
	struct hostlist *yppush_hostlist = NULL;
	struct hostlist *tmp;

	while ((ch = getopt(argc, argv, "d:j:p:h:t:v")) != -1) {
		switch (ch) {
		case 'd':
			yppush_domain = optarg;
			break;
		case 'j':
			yppush_jobs = atoi(optarg);
			if (yppush_jobs <= 0)
				yppush_jobs = 1;
			break;
		case 'p':
			yp_dir = optarg;
			break;
		case 'h': /* we can handle multiple hosts */
			if ((tmp = (struct hostlist *)malloc(sizeof(struct hostlist))) == NULL) {
				yp_error("malloc failed");
				yppush_exit(1);
			}
			tmp->name = strdup(optarg);
			tmp->next = yppush_hostlist;
			yppush_hostlist = tmp;
			break;
		case 't':
			yppush_timeout = atoi(optarg);
			break;
		case 'v':
			verbose++;
			break;
		default:
			usage();
			break;
		}
	}

	argc -= optind;
	argv += optind;

	yppush_mapname = argv[0];

	if (yppush_mapname == NULL) {
	/* "No guts, no glory." */
		usage();
	}

	/*
	 * If no domain was specified, try to find the default
	 * domain. If we can't find that, we're doomed and must bail.
	 */
	if (yppush_domain == NULL) {
		char *yppush_check_domain;
		if (!yp_get_default_domain(&yppush_check_domain) &&
			!_yp_check(&yppush_check_domain)) {
			yp_error("no domain specified and NIS not running");
			usage();
		} else
			yp_get_default_domain(&yppush_domain);
	}

	/* Check to see that we are the master for this map. */

	if (gethostname ((char *)&myname, sizeof(myname))) {
		yp_error("failed to get name of local host: %s",
			strerror(errno));
		yppush_exit(1);
	}

	key.data = "YP_MASTER_NAME";
	key.size = sizeof("YP_MASTER_NAME") - 1;

	if (yp_get_record(yppush_domain, yppush_mapname,
			  &key, &data, 1) != YP_TRUE) {
		yp_error("couldn't open %s map: %s", yppush_mapname,
			 strerror(errno));
		yppush_exit(1);
	}

	if (strncasecmp(myname, data.data, data.size) == 0) {
		/* I am master server, and no explicit host list was
		   specified: do not push map to myself -- this will
		   fail with YPPUSH_AGE anyway. */
		if (yppush_hostlist == NULL)
			skip_master = 1;
	} else {
		yp_error("warning: this host is not the master for %s",
							yppush_mapname);
#ifdef NITPICKY
		yppush_exit(1);
#endif
	}

	yppush_master = malloc(data.size + 1);
	strncpy(yppush_master, data.data, data.size);
	yppush_master[data.size] = '\0';

	/* Install some handy handlers. */
	signal(SIGTERM, handler);
	signal(SIGINT, handler);

	/* set initial transaction ID */
	yppush_transid = time((time_t *)NULL);

	if (yppush_hostlist) {
	/*
	 * Host list was specified on the command line:
	 * kick off the transfers by hand.
	 */
		tmp = yppush_hostlist;
		while (tmp) {
			yppush_foreach(YP_TRUE, NULL, 0, tmp->name,
			    strlen(tmp->name), NULL);
			tmp = tmp->next;
		}
	} else {
	/*
	 * Do a yp_all() on the ypservers map and initiate a ypxfr
	 * for each one.
	 */
		ypxfr_get_map("ypservers", yppush_domain,
			      "localhost", yppush_foreach);
	}

	if (verbose > 1)
		yp_error("all jobs dispatched");

	/* All done -- normal exit. */
	yppush_exit(0);

	/* Just in case. */
	exit(0);
}