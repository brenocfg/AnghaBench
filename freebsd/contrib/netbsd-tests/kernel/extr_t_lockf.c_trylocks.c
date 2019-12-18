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
struct flock {int l_start; int l_len; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int filesize ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  lockfile ; 
 int nlocks ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int random_uint32 () ; 
 int /*<<< orphan*/  sleeptime ; 
 int /*<<< orphan*/  srand48 (int /*<<< orphan*/ ) ; 
 scalar_t__ usleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trylocks(int id)
{
	int i, fd;

	srand48(getpid());

	fd = open (lockfile, O_RDWR, 0);
        
	if (fd < 0)
		err(1, "%s", lockfile);

	printf("%d: start\n", id);

	for (i = 0; i < nlocks; i++) {
		struct flock fl;

		fl.l_start = random_uint32() % filesize;
		fl.l_len = random_uint32() % filesize;
		switch (random_uint32() % 3) {
		case 0:
			fl.l_type = F_RDLCK;
			break;
		case 1:
			fl.l_type = F_WRLCK;
			break;
		case 2:
			fl.l_type = F_UNLCK;
			break;
		}
		fl.l_whence = SEEK_SET;

		(void)fcntl(fd, F_SETLKW, &fl);

		if (usleep(sleeptime) < 0) 
#if defined(__FreeBSD__)
		  if (errno != EINTR)
#endif
		  err(1, "usleep");
	}
	printf("%d: done\n", id);
	close (fd);
}