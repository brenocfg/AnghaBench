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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct fifolog_file {scalar_t__ fd; int recsize; int logsize; int /*<<< orphan*/ * zs; int /*<<< orphan*/ * recbuf; } ;
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  FIFOLOG_FMT_MAGIC ; 
 int FIFOLOG_OFF_BS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int be32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int fstat (scalar_t__,struct stat*) ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 void* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int pread (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
fifolog_int_open_i(struct fifolog_file *f, const char *fname, int mode)
{
	struct stat st;
	ssize_t u;
	int i;

	f->fd = open(fname, mode ? O_RDWR : O_RDONLY);
	if (f->fd < 0)
		return ("Cannot open");

	/* Determine initial record size guesstimate */
	i = ioctl(f->fd, DIOCGSECTORSIZE, &f->recsize);
	if (i != 0 && errno != ENOTTY)
		return ("ioctl(DIOCGSECTORSIZE) failed");

	if (i != 0) {
		i = fstat(f->fd, &st);
		assert(i == 0);
		if (!S_ISREG(st.st_mode))
			return ("Neither disk nor regular file");
		f->recsize = 512;
		f->logsize = st.st_size;
	} else if (f->recsize < 64) {
		return ("Disk device sectorsize smaller than 64");
	} else {
		i = ioctl(f->fd, DIOCGMEDIASIZE, &f->logsize);
		if (i < 0 && errno != ENOTTY)
			return ("ioctl(DIOCGMEDIASIZE) failed");
	}

	/* Allocate a record buffer */
	f->recbuf = malloc(f->recsize);
	if (f->recbuf == NULL)
		return ("Cannot malloc");

	/* Read and validate the label sector */
	i = pread(f->fd, f->recbuf, f->recsize, 0);
	if (i < 0 || i < (int)f->recsize)
		return ("Read error, first sector");

	errno = 0;
	if (memcmp(f->recbuf, FIFOLOG_FMT_MAGIC, strlen(FIFOLOG_FMT_MAGIC) + 1))
		return ("Wrong or missing magic string");

	u = be32dec(f->recbuf + FIFOLOG_OFF_BS);
	if (u < 64)
		return ("Wrong record size in header (<64)");

	if ((off_t)u >= f->logsize)
		return ("Record size in header bigger than fifolog");

	f->recsize = u;

	/* Reallocate the buffer to correct size if necessary */
	if (u != f->recsize) {
		free(f->recbuf);
		f->recbuf = NULL;
		f->recsize = u;
		f->recbuf = malloc(f->recsize);
		if (f->recbuf == NULL)
			return ("Cannot malloc");
	}

	/* Calculate number of records in fifolog */
	f->logsize /= u;
	if (f->logsize < 10)
		return ("less than 10 records in fifolog");

	f->logsize--;		/* the label record */

	/* Initialize zlib handling */

	f->zs = calloc(1, sizeof(*f->zs));
	if (f->zs == NULL)
		return ("cannot malloc");

	return (NULL);
}