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
typedef  char u_char ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BZFILE ;

/* Variables and functions */
 scalar_t__ BZ2_bzRead (int*,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  BZ2_bzReadClose (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BZ2_bzReadOpen (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int BZ_STREAM_END ; 
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_SEEK ; 
 int /*<<< orphan*/  CAP_UNLINKAT ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int HEADER_SIZE ; 
 scalar_t__ INT_MAX ; 
 int OFF_MAX ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_DIRECTORY ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SSIZE_MAX ; 
 scalar_t__ add_off_t (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * basename (char*) ; 
 scalar_t__ cap_enter () ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ cap_rights_limit (int,int /*<<< orphan*/ *) ; 
 int close (int) ; 
 int dirfd ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit_cleanup ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/ * newfile ; 
 scalar_t__ offtin (char*) ; 
 int open (char*,int,...) ; 
 int openat (int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

int main(int argc, char *argv[])
{
	FILE *f, *cpf, *dpf, *epf;
	BZFILE *cpfbz2, *dpfbz2, *epfbz2;
	char *directory, *namebuf;
	int cbz2err, dbz2err, ebz2err;
	int newfd, oldfd;
	off_t oldsize, newsize;
	off_t bzctrllen, bzdatalen;
	u_char header[HEADER_SIZE], buf[8];
	u_char *old, *new;
	off_t oldpos, newpos;
	off_t ctrl[3];
	off_t i, lenread, offset;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights_dir, rights_ro, rights_wr;
#endif

	if (argc != 4)
		usage();

	/* Open patch file */
	if ((f = fopen(argv[3], "rb")) == NULL)
		err(1, "fopen(%s)", argv[3]);
	/* Open patch file for control block */
	if ((cpf = fopen(argv[3], "rb")) == NULL)
		err(1, "fopen(%s)", argv[3]);
	/* open patch file for diff block */
	if ((dpf = fopen(argv[3], "rb")) == NULL)
		err(1, "fopen(%s)", argv[3]);
	/* open patch file for extra block */
	if ((epf = fopen(argv[3], "rb")) == NULL)
		err(1, "fopen(%s)", argv[3]);
	/* open oldfile */
	if ((oldfd = open(argv[1], O_RDONLY | O_BINARY, 0)) < 0)
		err(1, "open(%s)", argv[1]);
	/* open directory where we'll write newfile */
	if ((namebuf = strdup(argv[2])) == NULL ||
	    (directory = dirname(namebuf)) == NULL ||
	    (dirfd = open(directory, O_DIRECTORY)) < 0)
		err(1, "open %s", argv[2]);
	free(namebuf);
	if ((newfile = basename(argv[2])) == NULL)
		err(1, "basename");
	/* open newfile */
	if ((newfd = openat(dirfd, newfile,
	    O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0666)) < 0)
		err(1, "open(%s)", argv[2]);
	atexit(exit_cleanup);

#ifndef WITHOUT_CAPSICUM
	if (cap_enter() < 0)
		err(1, "failed to enter security sandbox");

	cap_rights_init(&rights_ro, CAP_READ, CAP_FSTAT, CAP_SEEK);
	cap_rights_init(&rights_wr, CAP_WRITE);
	cap_rights_init(&rights_dir, CAP_UNLINKAT);

	if (cap_rights_limit(fileno(f), &rights_ro) < 0 ||
	    cap_rights_limit(fileno(cpf), &rights_ro) < 0 ||
	    cap_rights_limit(fileno(dpf), &rights_ro) < 0 ||
	    cap_rights_limit(fileno(epf), &rights_ro) < 0 ||
	    cap_rights_limit(oldfd, &rights_ro) < 0 ||
	    cap_rights_limit(newfd, &rights_wr) < 0 ||
	    cap_rights_limit(dirfd, &rights_dir) < 0)
		err(1, "cap_rights_limit() failed, could not restrict"
		    " capabilities");
#endif

	/*
	File format:
		0	8	"BSDIFF40"
		8	8	X
		16	8	Y
		24	8	sizeof(newfile)
		32	X	bzip2(control block)
		32+X	Y	bzip2(diff block)
		32+X+Y	???	bzip2(extra block)
	with control block a set of triples (x,y,z) meaning "add x bytes
	from oldfile to x bytes from the diff block; copy y bytes from the
	extra block; seek forwards in oldfile by z bytes".
	*/

	/* Read header */
	if (fread(header, 1, HEADER_SIZE, f) < HEADER_SIZE) {
		if (feof(f))
			errx(1, "Corrupt patch");
		err(1, "fread(%s)", argv[3]);
	}

	/* Check for appropriate magic */
	if (memcmp(header, "BSDIFF40", 8) != 0)
		errx(1, "Corrupt patch");

	/* Read lengths from header */
	bzctrllen = offtin(header + 8);
	bzdatalen = offtin(header + 16);
	newsize = offtin(header + 24);
	if (bzctrllen < 0 || bzctrllen > OFF_MAX - HEADER_SIZE ||
	    bzdatalen < 0 || bzctrllen + HEADER_SIZE > OFF_MAX - bzdatalen ||
	    newsize < 0 || newsize > SSIZE_MAX)
		errx(1, "Corrupt patch");

	/* Close patch file and re-open it via libbzip2 at the right places */
	if (fclose(f))
		err(1, "fclose(%s)", argv[3]);
	offset = HEADER_SIZE;
	if (fseeko(cpf, offset, SEEK_SET))
		err(1, "fseeko(%s, %jd)", argv[3], (intmax_t)offset);
	if ((cpfbz2 = BZ2_bzReadOpen(&cbz2err, cpf, 0, 0, NULL, 0)) == NULL)
		errx(1, "BZ2_bzReadOpen, bz2err = %d", cbz2err);
	offset = add_off_t(offset, bzctrllen);
	if (fseeko(dpf, offset, SEEK_SET))
		err(1, "fseeko(%s, %jd)", argv[3], (intmax_t)offset);
	if ((dpfbz2 = BZ2_bzReadOpen(&dbz2err, dpf, 0, 0, NULL, 0)) == NULL)
		errx(1, "BZ2_bzReadOpen, bz2err = %d", dbz2err);
	offset = add_off_t(offset, bzdatalen);
	if (fseeko(epf, offset, SEEK_SET))
		err(1, "fseeko(%s, %jd)", argv[3], (intmax_t)offset);
	if ((epfbz2 = BZ2_bzReadOpen(&ebz2err, epf, 0, 0, NULL, 0)) == NULL)
		errx(1, "BZ2_bzReadOpen, bz2err = %d", ebz2err);

	if ((oldsize = lseek(oldfd, 0, SEEK_END)) == -1 ||
	    oldsize > SSIZE_MAX ||
	    (old = malloc(oldsize)) == NULL ||
	    lseek(oldfd, 0, SEEK_SET) != 0 ||
	    read(oldfd, old, oldsize) != oldsize ||
	    close(oldfd) == -1)
		err(1, "%s", argv[1]);
	if ((new = malloc(newsize)) == NULL)
		err(1, NULL);

	oldpos = 0;
	newpos = 0;
	while (newpos < newsize) {
		/* Read control data */
		for (i = 0; i <= 2; i++) {
			lenread = BZ2_bzRead(&cbz2err, cpfbz2, buf, 8);
			if ((lenread < 8) || ((cbz2err != BZ_OK) &&
			    (cbz2err != BZ_STREAM_END)))
				errx(1, "Corrupt patch");
			ctrl[i] = offtin(buf);
		}

		/* Sanity-check */
		if (ctrl[0] < 0 || ctrl[0] > INT_MAX ||
		    ctrl[1] < 0 || ctrl[1] > INT_MAX)
			errx(1, "Corrupt patch");

		/* Sanity-check */
		if (add_off_t(newpos, ctrl[0]) > newsize)
			errx(1, "Corrupt patch");

		/* Read diff string */
		lenread = BZ2_bzRead(&dbz2err, dpfbz2, new + newpos, ctrl[0]);
		if ((lenread < ctrl[0]) ||
		    ((dbz2err != BZ_OK) && (dbz2err != BZ_STREAM_END)))
			errx(1, "Corrupt patch");

		/* Add old data to diff string */
		for (i = 0; i < ctrl[0]; i++)
			if (add_off_t(oldpos, i) < oldsize)
				new[newpos + i] += old[oldpos + i];

		/* Adjust pointers */
		newpos = add_off_t(newpos, ctrl[0]);
		oldpos = add_off_t(oldpos, ctrl[0]);

		/* Sanity-check */
		if (add_off_t(newpos, ctrl[1]) > newsize)
			errx(1, "Corrupt patch");

		/* Read extra string */
		lenread = BZ2_bzRead(&ebz2err, epfbz2, new + newpos, ctrl[1]);
		if ((lenread < ctrl[1]) ||
		    ((ebz2err != BZ_OK) && (ebz2err != BZ_STREAM_END)))
			errx(1, "Corrupt patch");

		/* Adjust pointers */
		newpos = add_off_t(newpos, ctrl[1]);
		oldpos = add_off_t(oldpos, ctrl[2]);
	}

	/* Clean up the bzip2 reads */
	BZ2_bzReadClose(&cbz2err, cpfbz2);
	BZ2_bzReadClose(&dbz2err, dpfbz2);
	BZ2_bzReadClose(&ebz2err, epfbz2);
	if (fclose(cpf) || fclose(dpf) || fclose(epf))
		err(1, "fclose(%s)", argv[3]);

	/* Write the new file */
	if (write(newfd, new, newsize) != newsize || close(newfd) == -1)
		err(1, "%s", argv[2]);
	/* Disable atexit cleanup */
	newfile = NULL;

	free(new);
	free(old);

	return (0);
}