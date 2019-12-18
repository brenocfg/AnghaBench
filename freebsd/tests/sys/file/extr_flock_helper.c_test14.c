#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbuf ;
struct TYPE_4__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; } ;
struct flock {int l_start; int l_len; int l_type; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  outbuf ;

/* Variables and functions */
 int CHILD_COUNT ; 
 scalar_t__ EDEADLK ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FAIL (int) ; 
 void* F_RDLCK ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int F_UNLCK ; 
 void* F_WRLCK ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SUCCEED ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pread (int,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pwrite (int,char*,int,int) ; 
 int random () ; 
 scalar_t__ safe_waitpid (int) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,...) ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
test14(int fd, int argc, const char **argv)
{
#define CHILD_COUNT 20
	/*
	 * We create a set of child processes and let each one run
	 * through a random sequence of locks and unlocks.
	 */
	int i, j, id, id_base;
	int pids[CHILD_COUNT], pid;
	char buf[128];
	char tbuf[128];
	int map[128];
	char outbuf[512];
	struct flock fl;
	struct itimerval itv;
	int status;

	id_base = 0;
	if (argc >= 2)
		id_base = strtol(argv[1], NULL, 0);

	printf("14 - soak test: ");
	fflush(stdout);

	for (i = 0; i < 128; i++)
		map[i] = F_UNLCK;

	for (i = 0; i < CHILD_COUNT; i++) {

		pid = fork();
		if (pid < 0)
			err(1, "fork");
		if (pid) {
			/*
			 * Parent - record the pid and continue.
			 */
			pids[i] = pid;
			continue;
		}

		/*
		 * Child - do some work and exit.
		 */
		id = id_base + i;
		srandom(getpid());

		for (j = 0; j < 50; j++) {
			int start, end, len;
			int set, wrlock;

			do {
				start = random() & 127;
				end = random() & 127;
			} while (end <= start);

			set = random() & 1;
			wrlock = random() & 1;

			len = end - start;
			fl.l_start = start;
			fl.l_len = len;
			fl.l_whence = SEEK_SET;
			if (set)
				fl.l_type = wrlock ? F_WRLCK : F_RDLCK;
			else
				fl.l_type = F_UNLCK;

			itv.it_interval.tv_sec = 0;
			itv.it_interval.tv_usec = 0;
			itv.it_value.tv_sec = 0;
			itv.it_value.tv_usec = 3000;
			setitimer(ITIMER_REAL, &itv, NULL);

			if (fcntl(fd, F_SETLKW, &fl) < 0) {
				if (errno == EDEADLK || errno == EINTR) {
					if (verbose) {
						snprintf(outbuf, sizeof(outbuf),
						    "%d[%d]: %s [%d .. %d] %s\n",
						    id, j,
						    set ? (wrlock ? "write lock"
							: "read lock")
						    : "unlock", start, end,
						    errno == EDEADLK
						    ? "deadlock"
						    : "interrupted");
						write(1, outbuf,
						    strlen(outbuf));
					}
					continue;
				} else {
					perror("fcntl");
				}
			}

			itv.it_interval.tv_sec = 0;
			itv.it_interval.tv_usec = 0;
			itv.it_value.tv_sec = 0;
			itv.it_value.tv_usec = 0;
			setitimer(ITIMER_REAL, &itv, NULL);

			if (verbose) {
				snprintf(outbuf, sizeof(outbuf),
				    "%d[%d]: %s [%d .. %d] succeeded\n",
				    id, j,
				    set ? (wrlock ? "write lock" : "read lock")
				    : "unlock", start, end);
				write(1, outbuf, strlen(outbuf));
			}

			if (set) {
				if (wrlock) {
					/*
					 * We got a write lock - write
					 * our ID to each byte that we
					 * managed to claim.
					 */
					for (i = start; i < end; i++)
						map[i] = F_WRLCK;
					memset(&buf[start], id, len);
					if (pwrite(fd, &buf[start], len,
						start) != len) {
						printf("%d: short write\n", id);
						exit(1);
					}
				} else {
					/*
					 * We got a read lock - read
					 * the bytes which we claimed
					 * so that we can check that
					 * they don't change
					 * unexpectedly.
					 */
					for (i = start; i < end; i++)
						map[i] = F_RDLCK;
					if (pread(fd, &buf[start], len,
						start) != len) {
						printf("%d: short read\n", id);
						exit(1);
					}
				}
			} else {
				for (i = start; i < end; i++)
					map[i] = F_UNLCK;
			}

			usleep(1000);

			/*
			 * Read back the whole region so that we can
			 * check that all the bytes we have some kind
			 * of claim to have the correct value.
			 */
			if (pread(fd, tbuf, sizeof(tbuf), 0) != sizeof(tbuf)) {
				printf("%d: short read\n", id);
				exit(1);
			}

			for (i = 0; i < 128; i++) {
				if (map[i] != F_UNLCK && buf[i] != tbuf[i]) {
					snprintf(outbuf, sizeof(outbuf),
					    "%d: byte %d expected %d, "
					    "got %d\n", id, i, buf[i], tbuf[i]);
					write(1, outbuf, strlen(outbuf));
					exit(1);
				}
			}
		}
		if (verbose)
			printf("%d[%d]: done\n", id, j);

		exit(0);
	}

	status = 0;
	for (i = 0; i < CHILD_COUNT; i++) {
		status += safe_waitpid(pids[i]);
	}
	if (status)
		FAIL(status != 0);

	SUCCEED;
}