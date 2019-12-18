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
struct stat {int dummy; } ;

/* Variables and functions */
 int BUFSIZE ; 
 scalar_t__ EBADF ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* getprogname () ; 
 scalar_t__ memcmp (struct stat*,struct stat*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ write (int,char*,int) ; 

int
main(int argc, char **argv)
{
	int res = EXIT_SUCCESS;
	char buf[BUFSIZE];
	struct stat sb0, sb1;

	strcpy(buf, "test...");
	/* file desc 3 should be closed via addclose */
	if (read(3, buf, BUFSIZE) != -1 || errno != EBADF) {
		fprintf(stderr, "%s: filedesc 3 is not closed\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	/* file desc 4 should be closed via closeonexec */
	if (read(4, buf, BUFSIZE) != -1 || errno != EBADF) {
		fprintf(stderr, "%s: filedesc 4 is not closed\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	/* file desc 5 remains open */
	if (write(5, buf, BUFSIZE) <= 0) {
		fprintf(stderr, "%s: could not write to filedesc 5\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	/* file desc 6 should be open (via addopen) */
	if (write(6, buf, BUFSIZE) <= 0) {
		fprintf(stderr, "%s: could not write to filedesc 6\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	/* file desc 7 should refer to stdout */
	fflush(stdout);
	if (fstat(fileno(stdout), &sb0) != 0) {
		fprintf(stderr, "%s: could not fstat stdout\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	if (fstat(7, &sb1) != 0) {
		fprintf(stderr, "%s: could not fstat filedesc 7\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	if (write(7, buf, strlen(buf)) <= 0) {
		fprintf(stderr, "%s: could not write to filedesc 7\n",
		    getprogname());
		res = EXIT_FAILURE;
	}
	if (memcmp(&sb0, &sb1, sizeof sb0) != 0) {
		fprintf(stderr, "%s: stat results differ\n", getprogname());
		res = EXIT_FAILURE;
	}

	return res;
}