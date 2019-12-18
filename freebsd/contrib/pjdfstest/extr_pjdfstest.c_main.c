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
struct syscall_desc {int dummy; } ;

/* Variables and functions */
 unsigned int call_syscall (struct syscall_desc*,char**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 struct syscall_desc* find_syscall (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  set_gids (char*) ; 
 scalar_t__ setuid (int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct syscall_desc *scall;
	unsigned int n;
	char *gids, *endp;
	int uid, umsk, ch;

	uid = -1;
	gids = NULL;
	umsk = 0;

	while ((ch = getopt(argc, argv, "g:u:U:")) != -1) {
		switch(ch) {
		case 'g':
			gids = optarg;
			break;
		case 'u':
			uid = (int)strtol(optarg, &endp, 0);
			if (*endp != '\0' && !isspace((unsigned char)*endp)) {
				fprintf(stderr, "invalid uid '%s' - number "
				    "expected\n", optarg);
				exit(1);
			}
			break;
		case 'U':
			umsk = (int)strtol(optarg, &endp, 0);
			if (*endp != '\0' && !isspace((unsigned char)*endp)) {
				fprintf(stderr, "invalid umask '%s' - number "
				    "expected\n", optarg);
				exit(1);
			}
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		fprintf(stderr, "too few arguments\n");
		usage();
	}

	if (gids != NULL) {
		fprintf(stderr, "changing groups to %s\n", gids);
		set_gids(gids);
	}
	if (uid != -1) {
		fprintf(stderr, "changing uid to %d\n", uid);
		if (setuid(uid) < 0) {
			fprintf(stderr, "cannot change uid: %s\n",
			    strerror(errno));
			exit(1);
		}
	}

	/* Change umask to requested value or to 0, if not requested. */
	umask(umsk);

	for (;;) {
		scall = find_syscall(argv[0]);
		if (scall == NULL) {
			fprintf(stderr, "syscall '%s' not supported\n",
			    argv[0]);
			exit(1);
		}
		argc++;
		argv++;
		n = call_syscall(scall, argv);
		argc += n;
		argv += n;
		if (argv[0] == NULL)
			break;
		argc++;
		argv++;
	}

	exit(0);
}