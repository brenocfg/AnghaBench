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
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  tm ;
typedef  int /*<<< orphan*/  timestr ;
struct tm {int tm_hour; int tm_min; int tm_sec; } ;
struct passwd {void* pw_uid; } ;
struct group {void* gr_gid; } ;
typedef  scalar_t__ pid_t ;
typedef  void* au_event_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  ISOPTSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_A ; 
 int /*<<< orphan*/  OPT_a ; 
 int /*<<< orphan*/  OPT_b ; 
 int /*<<< orphan*/  OPT_c ; 
 int /*<<< orphan*/  OPT_d ; 
 int /*<<< orphan*/  OPT_e ; 
 int /*<<< orphan*/  OPT_f ; 
 int /*<<< orphan*/  OPT_g ; 
 int /*<<< orphan*/  OPT_j ; 
 int /*<<< orphan*/  OPT_m ; 
 int /*<<< orphan*/  OPT_r ; 
 int /*<<< orphan*/  OPT_u ; 
 int /*<<< orphan*/  OPT_v ; 
 int /*<<< orphan*/  SETOPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  bzero (struct tm*,int) ; 
 int cap_enter () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getauditflagsbin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void** getauevnonam (int /*<<< orphan*/ ) ; 
 struct group* getgrnam (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 void** malloc (int) ; 
 int /*<<< orphan*/  maskp ; 
 void* mktime (struct tm*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  opttochk ; 
 void* p_atime ; 
 void* p_auid ; 
 void* p_btime ; 
 void* p_egid ; 
 void* p_euid ; 
 void** p_evec ; 
 int p_evec_alloc ; 
 int p_evec_used ; 
 void* p_rgid ; 
 void* p_ruid ; 
 void* p_subid ; 
 int /*<<< orphan*/  parse_object_type (int /*<<< orphan*/ ,char*) ; 
 void** realloc (void**,int) ; 
 int select_records (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  strptime (int /*<<< orphan*/ ,char*,struct tm*) ; 
 void* strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  usage (char*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	struct group *grp;
	struct passwd *pw;
	struct tm tm;
	au_event_t *n;
	FILE *fp;
	int i;
	char *objval, *converr;
	int ch;
	char timestr[128];
	char *fname;
	uint16_t *etp;
#ifdef HAVE_CAP_ENTER
	int retval, status;
	pid_t childpid, pid;
#endif

	converr = NULL;

	while ((ch = getopt(argc, argv, "Aa:b:c:d:e:f:g:j:m:o:r:u:v")) != -1) {
		switch(ch) {
		case 'A':
			SETOPT(opttochk, OPT_A);
			break;

		case 'a':
			if (ISOPTSET(opttochk, OPT_a)) {
				usage("d is exclusive with a and b");
			}
			SETOPT(opttochk, OPT_a);
			bzero(&tm, sizeof(tm));
			strptime(optarg, "%Y%m%d%H%M%S", &tm);
			strftime(timestr, sizeof(timestr), "%Y%m%d%H%M%S",
			    &tm);
			/* fprintf(stderr, "Time converted = %s\n", timestr); */
			p_atime = mktime(&tm);
			break; 	

		case 'b':
			if (ISOPTSET(opttochk, OPT_b)) {
				usage("d is exclusive with a and b");
			}
			SETOPT(opttochk, OPT_b);
			bzero(&tm, sizeof(tm));
			strptime(optarg, "%Y%m%d%H%M%S", &tm);
			strftime(timestr, sizeof(timestr), "%Y%m%d%H%M%S",
			    &tm);
			/* fprintf(stderr, "Time converted = %s\n", timestr); */
			p_btime = mktime(&tm);
			break; 	

		case 'c':
			if (0 != getauditflagsbin(optarg, &maskp)) {
				/* Incorrect class */
				usage("Incorrect class");
			}
			SETOPT(opttochk, OPT_c);
			break;

		case 'd':
			if (ISOPTSET(opttochk, OPT_b) || ISOPTSET(opttochk,
			    OPT_a))
				usage("'d' is exclusive with 'a' and 'b'");
			SETOPT(opttochk, OPT_d);
			bzero(&tm, sizeof(tm));
			strptime(optarg, "%Y%m%d", &tm);
			strftime(timestr, sizeof(timestr), "%Y%m%d", &tm);
			/* fprintf(stderr, "Time converted = %s\n", timestr); */
			p_atime = mktime(&tm);
			tm.tm_hour = 23;
			tm.tm_min = 59;
			tm.tm_sec = 59;
			strftime(timestr, sizeof(timestr), "%Y%m%d", &tm);
			/* fprintf(stderr, "Time converted = %s\n", timestr); */
			p_btime = mktime(&tm);
			break;

		case 'e':
			p_euid = strtol(optarg, &converr, 10);
			if (*converr != '\0') {
				/* Try the actual name */
				if ((pw = getpwnam(optarg)) == NULL)
					break;
				p_euid = pw->pw_uid;
			}
			SETOPT(opttochk, OPT_e);
			break;

		case 'f':
			p_egid = strtol(optarg, &converr, 10);
			if (*converr != '\0') {
				/* Try actual group name. */
				if ((grp = getgrnam(optarg)) == NULL)
					break;
				p_egid = grp->gr_gid;
			}
			SETOPT(opttochk, OPT_f);
			break;

		case 'g':
			p_rgid = strtol(optarg, &converr, 10);
			if (*converr != '\0') {
				/* Try actual group name. */
				if ((grp = getgrnam(optarg)) == NULL) 
					break;
				p_rgid = grp->gr_gid;
			}
			SETOPT(opttochk, OPT_g);
			break;

		case 'j':
			p_subid = strtol(optarg, (char **)NULL, 10);
			SETOPT(opttochk, OPT_j);
			break;

		case 'm':
			if (p_evec == NULL) {
				p_evec_alloc = 32;
				p_evec = malloc(sizeof(*etp) * p_evec_alloc);
				if (p_evec == NULL)
					err(1, "malloc");
			} else if (p_evec_alloc == p_evec_used) {
				p_evec_alloc <<= 1;
				p_evec = realloc(p_evec,
				    sizeof(*p_evec) * p_evec_alloc);
				if (p_evec == NULL)
					err(1, "realloc");
			}
			etp = &p_evec[p_evec_used++];
			*etp = strtol(optarg, (char **)NULL, 10);
			if (*etp == 0) {
				/* Could be the string representation. */
				n = getauevnonam(optarg);
				if (n == NULL)
					usage("Incorrect event name");
				*etp = *n;
			}
			SETOPT(opttochk, OPT_m);
			break;

		case 'o':
			objval = strchr(optarg, '=');
			if (objval != NULL) {
				*objval = '\0';
				objval += 1;			
				parse_object_type(optarg, objval);
			}
			break;

		case 'r':
			p_ruid = strtol(optarg, &converr, 10);
			if (*converr != '\0') {
				if ((pw = getpwnam(optarg)) == NULL)
					break;
				p_ruid = pw->pw_uid;
			}
			SETOPT(opttochk, OPT_r);
			break;

		case 'u':
			p_auid = strtol(optarg, &converr, 10);
			if (*converr != '\0') {
				if ((pw = getpwnam(optarg)) == NULL)
					break;
				p_auid = pw->pw_uid;
			}
			SETOPT(opttochk, OPT_u);
			break;

		case 'v':
			SETOPT(opttochk, OPT_v);
			break;

		case '?':
		default:
			usage("Unknown option");
		}
	}
	argv += optind;
	argc -= optind;

	if (argc == 0) {
#ifdef HAVE_CAP_ENTER
		retval = cap_enter();
		if (retval != 0 && errno != ENOSYS)
			err(EXIT_FAILURE, "cap_enter");
#endif
		if (select_records(stdin) == -1)
			errx(EXIT_FAILURE,
			    "Couldn't select records from stdin");
		exit(EXIT_SUCCESS);
	}

	/*
	 * XXX: We should actually be merging records here.
	 */
	for (i = 0; i < argc; i++) {
		fname = argv[i];
		fp = fopen(fname, "r");
		if (fp == NULL)
			errx(EXIT_FAILURE, "Couldn't open %s", fname);

		/*
		 * If operating with sandboxing, create a sandbox process for
		 * each trail file we operate on.  This avoids the need to do
		 * fancy things with file descriptors, etc, when iterating on
		 * a list of arguments.
		 *
		 * NB: Unlike praudit(1), auditreduce(1) terminates if it hits
		 * any errors.  Propagate the error from the child to the
		 * parent if any problems arise.
		 */
#ifdef HAVE_CAP_ENTER
		childpid = fork();
		if (childpid == 0) {
			/* Child. */
			retval = cap_enter();
			if (retval != 0 && errno != ENOSYS)
				errx(EXIT_FAILURE, "cap_enter");
			if (select_records(fp) == -1)
				errx(EXIT_FAILURE,
				    "Couldn't select records %s", fname);
			exit(0);
		}

		/* Parent.  Await child termination, check exit value. */
		while ((pid = waitpid(childpid, &status, 0)) != childpid);
		if (WEXITSTATUS(status) != 0)
			exit(EXIT_FAILURE);
#else
		if (select_records(fp) == -1)
			errx(EXIT_FAILURE, "Couldn't select records %s",
			    fname);
#endif
		fclose(fp);
	}
	exit(EXIT_SUCCESS);
}