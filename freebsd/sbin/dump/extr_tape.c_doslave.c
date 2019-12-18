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
struct req {size_t count; scalar_t__ dblk; } ;
struct TYPE_2__ {scalar_t__* tblock; struct req* req; } ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int TP_BSIZE ; 
 int atomic (int (*) (int /*<<< orphan*/ ,scalar_t__,int),int,char*,int) ; 
 int /*<<< orphan*/  blkread (scalar_t__,scalar_t__,int) ; 
 scalar_t__ caught ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  diskfd ; 
 scalar_t__ errno ; 
 scalar_t__ host ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int master ; 
 size_t ntrec ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  quit (char*,...) ; 
 int read (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int ready ; 
 int reqsiz ; 
 int rmtwrite (scalar_t__,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigpause (int /*<<< orphan*/ ) ; 
 TYPE_1__* slp ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  tapefd ; 
 size_t trecno ; 
 int write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int writesize ; 

__attribute__((used)) static void
doslave(int cmd, int slave_number)
{
	int nread;
	int nextslave, size, wrote, eot_count;

	/*
	 * Need our own seek pointer.
	 */
	(void) close(diskfd);
	if ((diskfd = open(disk, O_RDONLY)) < 0)
		quit("slave couldn't reopen disk: %s\n", strerror(errno));

	/*
	 * Need the pid of the next slave in the loop...
	 */
	if ((nread = atomic(read, cmd, (char *)&nextslave, sizeof nextslave))
	    != sizeof nextslave) {
		quit("master/slave protocol botched - didn't get pid of next slave.\n");
	}

	/*
	 * Get list of blocks to dump, read the blocks into tape buffer
	 */
	while ((nread = atomic(read, cmd, (char *)slp->req, reqsiz)) == reqsiz) {
		struct req *p = slp->req;

		for (trecno = 0; trecno < ntrec;
		     trecno += p->count, p += p->count) {
			if (p->dblk) {
				blkread(p->dblk, slp->tblock[trecno],
					p->count * TP_BSIZE);
			} else {
				if (p->count != 1 || atomic(read, cmd,
				    (char *)slp->tblock[trecno],
				    TP_BSIZE) != TP_BSIZE)
				       quit("master/slave protocol botched.\n");
			}
		}
		if (setjmp(jmpbuf) == 0) {
			ready = 1;
			if (!caught)
				(void) pause();
		}
		ready = 0;
		caught = 0;

		/* Try to write the data... */
		eot_count = 0;
		size = 0;

		wrote = 0;
		while (eot_count < 10 && size < writesize) {
#ifdef RDUMP
			if (host)
				wrote = rmtwrite(slp->tblock[0]+size,
				    writesize-size);
			else
#endif
				wrote = write(tapefd, slp->tblock[0]+size,
				    writesize-size);
#ifdef WRITEDEBUG
			printf("slave %d wrote %d\n", slave_number, wrote);
#endif
			if (wrote < 0)
				break;
			if (wrote == 0)
				eot_count++;
			size += wrote;
		}

#ifdef WRITEDEBUG
		if (size != writesize)
		 printf("slave %d only wrote %d out of %d bytes and gave up.\n",
		     slave_number, size, writesize);
#endif

		/*
		 * Handle ENOSPC as an EOT condition.
		 */
		if (wrote < 0 && errno == ENOSPC) {
			wrote = 0;
			eot_count++;
		}

		if (eot_count > 0)
			size = 0;

		if (wrote < 0) {
			(void) kill(master, SIGUSR1);
			for (;;)
				(void) sigpause(0);
		} else {
			/*
			 * pass size of write back to master
			 * (for EOT handling)
			 */
			(void) atomic(write, cmd, (char *)&size, sizeof size);
		}

		/*
		 * If partial write, don't want next slave to go.
		 * Also jolts him awake.
		 */
		(void) kill(nextslave, SIGUSR2);
	}
	if (nread != 0)
		quit("error reading command pipe: %s\n", strerror(errno));
}