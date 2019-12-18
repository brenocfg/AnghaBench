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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mapper ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int write (int,char*,int) ; 

int
main(int argc, char **argv)
{
	int fd;
	char buf[BUFSIZ];
	pthread_t pt;

	if (argc != 2) {
		(void) printf("usage: %s <file name>\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1) {
		perror("open");
		exit(1);
	}

	if (pthread_create(&pt, NULL, mapper, &fd) != 0) {
		perror("pthread_create");
		exit(1);
	}
	for (;;) {
		if (write(fd, buf, sizeof (buf)) == -1) {
			perror("write");
			exit(1);
		}
	}

	/* NOTREACHED */
	return (0);
}