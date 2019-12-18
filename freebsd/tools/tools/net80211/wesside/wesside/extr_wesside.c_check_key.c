#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {double tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 TYPE_1__ real_start ; 
 int /*<<< orphan*/  time_print (char*,char*) ; 

void check_key() {
	char buf[1024];
	int fd;
	int rd;
	struct timeval now;

	fd = open(KEY_FILE, O_RDONLY);

	if (fd == -1) {
		return;
	}

	rd = read(fd, buf, sizeof(buf) -1);
	if (rd == -1) {
		perror("read()");
		exit(1);
	}

	buf[rd] = 0;

	close(fd);

	printf ("\n\n");
	time_print("KEY=(%s)\n", buf);

	if (gettimeofday(&now, NULL) == -1) {
		perror("gettimeofday()");
		exit(1);
	}

	printf ("Owned in %.02f minutes\n", 
		((double) now.tv_sec - real_start.tv_sec)/60.0);
	exit(0);
}