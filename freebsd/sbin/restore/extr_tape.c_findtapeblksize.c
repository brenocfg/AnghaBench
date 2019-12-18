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
struct s_spcl {scalar_t__ c_magic; } ;

/* Variables and functions */
 long TP_BSIZE ; 
 scalar_t__ blkcnt ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ host ; 
 int /*<<< orphan*/  mt ; 
 long ntrec ; 
 long numtrec ; 
 long read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 long rmtread (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tapebuf ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,long) ; 

__attribute__((used)) static void
findtapeblksize(void)
{
	long i;

	for (i = 0; i < ntrec; i++)
		((struct s_spcl *)&tapebuf[i * TP_BSIZE])->c_magic = 0;
	blkcnt = 0;
#ifdef RRESTORE
	if (host)
		i = rmtread(tapebuf, ntrec * TP_BSIZE);
	else
#endif
		i = read(mt, tapebuf, ntrec * TP_BSIZE);

	if (i <= 0) {
		fprintf(stderr, "tape read error: %s\n", strerror(errno));
		done(1);
	}
	if (i % TP_BSIZE != 0) {
		fprintf(stderr, "Tape block size (%ld) %s (%d)\n",
			i, "is not a multiple of dump block size", TP_BSIZE);
		done(1);
	}
	ntrec = i / TP_BSIZE;
	numtrec = ntrec;
	vprintf(stdout, "Tape block size is %ld\n", ntrec);
}