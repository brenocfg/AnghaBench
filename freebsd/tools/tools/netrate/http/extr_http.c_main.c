#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct state {char* path; int run_done; TYPE_2__* hwd; int /*<<< orphan*/  start_barrier; TYPE_5__ sin; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_8__ {scalar_t__ hwd_pid; scalar_t__ hwd_errorcount; scalar_t__ hwd_count; int /*<<< orphan*/  hwd_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int DEFAULTSECONDS ; 
 int DEFAULTTHREADS ; 
 int /*<<< orphan*/  INHERIT_SHARE ; 
 int /*<<< orphan*/  MAP_ANON ; 
 struct state* MAP_FAILED ; 
 int MAXTHREADS ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 int curthread ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ http_fetch (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_worker (TYPE_2__*) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  killall () ; 
 int /*<<< orphan*/  main_sighup ; 
 scalar_t__ minherit (struct state*,size_t,int /*<<< orphan*/ ) ; 
 struct state* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int numseconds ; 
 int numthreads ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_2__*),TYPE_2__*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t roundup (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_barrier_wakeup () ; 
 int /*<<< orphan*/  sleep (int) ; 
 struct state* statep ; 
 int threaded ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int ch, error, i;
	struct state *pagebuffer;
	uintmax_t total;
	size_t len;
	pid_t pid;

	numthreads = DEFAULTTHREADS;
	numseconds = DEFAULTSECONDS;
	while ((ch = getopt(argc, argv, "n:s:t")) != -1) {
		switch (ch) {
		case 'n':
			numthreads = atoi(optarg);
			break;

		case 's':
			numseconds = atoi(optarg);
			break;

		case 't':
			threaded = 1;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 3)
		usage();

	if (numthreads > MAXTHREADS)
		errx(-1, "%d exceeds max threads %d", numthreads,
		    MAXTHREADS);

	len = roundup(sizeof(struct state), getpagesize());
	pagebuffer = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
	if (pagebuffer == MAP_FAILED)
		err(-1, "mmap");
	if (minherit(pagebuffer, len, INHERIT_SHARE) < 0)
		err(-1, "minherit");
	statep = pagebuffer;

	bzero(&statep->sin, sizeof(statep->sin));
	statep->sin.sin_len = sizeof(statep->sin);
	statep->sin.sin_family = AF_INET;
	statep->sin.sin_addr.s_addr = inet_addr(argv[0]);
	statep->sin.sin_port = htons(atoi(argv[1]));
	statep->path = argv[2];

	/*
	 * Do one test retrieve so we can report the error from it, if any.
	 */
	if (http_fetch(&statep->sin, statep->path, 0) < 0)
		exit(-1);

	if (threaded) {
		if (pthread_barrier_init(&statep->start_barrier, NULL,
		    numthreads) != 0)
			err(-1, "pthread_barrier_init");
	}

	for (i = 0; i < numthreads; i++) {
		statep->hwd[i].hwd_count = 0;
		if (threaded) {
			if (pthread_create(&statep->hwd[i].hwd_thread, NULL,
			    http_worker, &statep->hwd[i]) != 0)
				err(-1, "pthread_create");
		} else {
			curthread = i;
			pid = fork();
			if (pid < 0) {
				error = errno;
				killall();
				errno = error;
				err(-1, "fork");
			}
			if (pid == 0) {
				http_worker(&statep->hwd[i]);
				printf("Doh\n");
				exit(0);
			}
			statep->hwd[i].hwd_pid = pid;
		}
	}
	if (!threaded) {
		signal(SIGHUP, main_sighup);
		sleep(2);
		signal_barrier_wakeup();
	}
	sleep(numseconds);
	statep->run_done = 1;
	if (!threaded)
		sleep(2);
	for (i = 0; i < numthreads; i++) {
		if (threaded) {
			if (pthread_join(statep->hwd[i].hwd_thread, NULL)
			    != 0)
				err(-1, "pthread_join");
		} else {
			pid = waitpid(statep->hwd[i].hwd_pid, NULL, 0);
			if (pid == statep->hwd[i].hwd_pid)
				statep->hwd[i].hwd_pid = 0;
		}
	}
	if (!threaded)
		killall();
	total = 0;
	for (i = 0; i < numthreads; i++)
		total += statep->hwd[i].hwd_count;
	printf("%ju transfers/second\n", total / numseconds);
	total = 0;
	for (i = 0; i < numthreads; i++)
		total += statep->hwd[i].hwd_errorcount;
	printf("%ju errors/second\n", total / numseconds);
	return (0);
}