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
union mfi_statrequest {int ms_item; TYPE_1__ ms_qstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFIIO_STATS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bzero (union mfi_statrequest*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,union mfi_statrequest*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	union mfi_statrequest sr;
	int fd, retval, queue;

	if (argc != 2)
		usage();

	fd = open("/dev/mfi0", O_RDWR);
	if (fd == -1) {
		printf("couldn't open mfi0: %s\n", strerror(errno));
		return (-1);
	}

	queue = atoi(argv[1]);
	printf("Getting stats for queue %d\n", queue);
	bzero(&sr, sizeof(union mfi_statrequest));
	sr.ms_item = queue;
	retval = ioctl(fd, MFIIO_STATS, &sr);
	if (retval == -1) {
		printf("error on ioctl: %s\n", strerror(errno));
		return (-1);
	}

	printf("length= %d, max= %d\n",sr.ms_qstat.q_length, sr.ms_qstat.q_max);

	close(fd);
	return 0;
}