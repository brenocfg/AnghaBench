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
typedef  char* uintmax_t ;
struct s_spcl {scalar_t__ c_magic; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int action; char* name; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
#define  SKIP 130 
 size_t TP_BSIZE ; 
#define  UNKNOWN 129 
#define  USING 128 
 int blkcnt ; 
 int /*<<< orphan*/  blksread ; 
 size_t byteslide ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*) ; 
 char endoftapemark ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getvol (long) ; 
 scalar_t__ host ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  mt ; 
 long ntrec ; 
 int numtrec ; 
 int /*<<< orphan*/  panic (char*,long,long) ; 
 scalar_t__ pipecmdin ; 
 scalar_t__ pipein ; 
 long read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reply (char*) ; 
 long rmtread (char*,int) ; 
 scalar_t__ rmtseek (long,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tapeaddr ; 
 char* tapebuf ; 
 int /*<<< orphan*/  terminateinput () ; 
 long volno ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  yflag ; 

__attribute__((used)) static void
readtape(char *buf)
{
	long rd, newvol, i, oldnumtrec;
	int cnt, seek_failed;

	if (blkcnt + (byteslide > 0) < numtrec) {
		memmove(buf, &tapebuf[(blkcnt++ * TP_BSIZE) + byteslide], (long)TP_BSIZE);
		blksread++;
		tapeaddr++;
		return;
	}
	if (numtrec > 0)
		memmove(&tapebuf[-TP_BSIZE],
		    &tapebuf[(numtrec-1) * TP_BSIZE], (long)TP_BSIZE);
	oldnumtrec = numtrec;
	for (i = 0; i < ntrec; i++)
		((struct s_spcl *)&tapebuf[i * TP_BSIZE])->c_magic = 0;
	if (numtrec == 0)
		numtrec = ntrec;
	cnt = ntrec * TP_BSIZE;
	rd = 0;
getmore:
#ifdef RRESTORE
	if (host)
		i = rmtread(&tapebuf[rd], cnt);
	else
#endif
		i = read(mt, &tapebuf[rd], cnt);
	/*
	 * Check for mid-tape short read error.
	 * If found, skip rest of buffer and start with the next.
	 */
	if (!pipein && !pipecmdin && numtrec < ntrec && i > 0) {
		dprintf(stdout, "mid-media short read error.\n");
		numtrec = ntrec;
	}
	/*
	 * Handle partial block read.
	 */
	if ((pipein || pipecmdin) && i == 0 && rd > 0)
		i = rd;
	else if (i > 0 && i != ntrec * TP_BSIZE) {
		if (pipein || pipecmdin) {
			rd += i;
			cnt -= i;
			if (cnt > 0)
				goto getmore;
			i = rd;
		} else {
			/*
			 * Short read. Process the blocks read.
			 */
			if (i % TP_BSIZE != 0)
				vprintf(stdout,
				    "partial block read: %ld should be %ld\n",
				    i, ntrec * TP_BSIZE);
			numtrec = i / TP_BSIZE;
		}
	}
	/*
	 * Handle read error.
	 */
	if (i < 0) {
		fprintf(stderr, "Tape read error while ");
		switch (curfile.action) {
		default:
			fprintf(stderr, "trying to set up tape\n");
			break;
		case UNKNOWN:
			fprintf(stderr, "trying to resynchronize\n");
			break;
		case USING:
			fprintf(stderr, "restoring %s\n", curfile.name);
			break;
		case SKIP:
			fprintf(stderr, "skipping over inode %ju\n",
			    (uintmax_t)curfile.ino);
			break;
		}
		if (!yflag && !reply("continue"))
			done(1);
		i = ntrec * TP_BSIZE;
		memset(tapebuf, 0, i);
#ifdef RRESTORE
		if (host)
			seek_failed = (rmtseek(i, 1) < 0);
		else
#endif
			seek_failed = (lseek(mt, i, SEEK_CUR) == (off_t)-1);

		if (seek_failed) {
			fprintf(stderr,
			    "continuation failed: %s\n", strerror(errno));
			done(1);
		}
	}
	/*
	 * Handle end of tape.
	 */
	if (i == 0) {
		vprintf(stdout, "End-of-tape encountered\n");
		if (!pipein) {
			newvol = volno + 1;
			volno = 0;
			numtrec = 0;
			getvol(newvol);
			readtape(buf);
			return;
		}
		if (rd % TP_BSIZE != 0)
			panic("partial block read: %ld should be %ld\n",
				rd, ntrec * TP_BSIZE);
		terminateinput();
		memmove(&tapebuf[rd], &endoftapemark, (long)TP_BSIZE);
	}
	if (oldnumtrec == 0)
		blkcnt = 0;
	else
		blkcnt -= oldnumtrec;
	memmove(buf,
	    &tapebuf[(blkcnt++ * TP_BSIZE) + byteslide], (long)TP_BSIZE);
	blksread++;
	tapeaddr++;
}