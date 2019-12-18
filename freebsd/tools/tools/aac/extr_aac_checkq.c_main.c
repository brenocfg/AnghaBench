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
struct TYPE_2__ {int q_length; int q_max; } ;
union aac_statrequest {int as_item; TYPE_1__ as_qstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AACIO_STATS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bzero (union aac_statrequest*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,union aac_statrequest*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	union aac_statrequest sr;
	int fd, retval, queue;

	if (argc != 2)
		usage();

	fd = open("/dev/aac0", O_RDWR);
	if (fd == -1) {
		printf("couldn't open aac0: %s\n", strerror(errno));
		return (-1);
	}

	queue = atoi(argv[1]);
	printf("Getting stats for queue %d\n", queue);
	bzero(&sr, sizeof(union aac_statrequest));
	sr.as_item = queue;
	retval = ioctl(fd, AACIO_STATS, &sr);
	if (retval == -1) {
		printf("error on ioctl: %s\n", strerror(errno));
		return (-1);
	}

	printf("length= %d, max= %d\n",sr.as_qstat.q_length, sr.as_qstat.q_max);

	close(fd);
	return 0;
}