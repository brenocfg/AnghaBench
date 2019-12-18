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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pidfile ; 
 int /*<<< orphan*/  remove_pidfile () ; 
 int /*<<< orphan*/  setsid () ; 

__attribute__((used)) static int daemonize(osm_opensm_t * osm)
{
	pid_t pid;
	int fd;
	FILE *f;

	fd = open("/dev/null", O_WRONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(-1);
	} else if (pid > 0)
		exit(0);

	setsid();

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(-1);
	} else if (pid > 0)
		exit(0);

	if (pidfile) {
		remove_pidfile();
		f = fopen(pidfile, "w");
		if (f) {
			fprintf(f, "%d\n", getpid());
			fclose(f);
		} else {
			perror("fopen");
			exit(1);
		}
	}

	close(0);
	close(1);
	close(2);

	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);

	return 0;
}