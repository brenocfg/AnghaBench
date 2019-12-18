#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct statvfs {int f_iosize; } ;
struct TYPE_7__ {scalar_t__ cs_nifree; scalar_t__ cs_ndir; scalar_t__ cs_nffree; scalar_t__ cs_nbfree; } ;
struct fs {TYPE_1__ fs_cstotal; scalar_t__ fs_time; } ;
typedef  scalar_t__ off_t ;
struct TYPE_8__ {scalar_t__ offset; int fd; scalar_t__ size; scalar_t__ inodes; void* superblock; scalar_t__ sparse; } ;
typedef  TYPE_2__ fsinfo_t ;
struct TYPE_10__ {scalar_t__ st_ino; scalar_t__ st_ctime; } ;
struct TYPE_9__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int DEBUG_FS_CREATE_IMAGE ; 
 int /*<<< orphan*/  MIN (int,scalar_t__) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* ctime (scalar_t__*) ; 
 int debug ; 
 char* ecalloc (int,int) ; 
 struct fs* ffs_mkfs (char const*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstatvfs (int,struct statvfs*) ; 
 int ftruncate (int,scalar_t__) ; 
 int lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  srandom (scalar_t__) ; 
 TYPE_4__ stampst ; 
 TYPE_3__ start_time ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char const*,long long,long long) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_create_image(const char *image, fsinfo_t *fsopts)
{
#if HAVE_STRUCT_STATVFS_F_IOSIZE && HAVE_FSTATVFS
	struct statvfs	sfs;
#endif
	struct fs	*fs;
	char	*buf;
	int	i, bufsize;
	off_t	bufrem;
	int	oflags = O_RDWR | O_CREAT;
	time_t	tstamp;

	assert (image != NULL);
	assert (fsopts != NULL);

		/* create image */
	if (fsopts->offset == 0)
		oflags |= O_TRUNC;
	if ((fsopts->fd = open(image, oflags, 0666)) == -1) {
		warn("Can't open `%s' for writing", image);
		return (-1);
	}

		/* zero image */
#if HAVE_STRUCT_STATVFS_F_IOSIZE && HAVE_FSTATVFS
	if (fstatvfs(fsopts->fd, &sfs) == -1) {
#endif
		bufsize = 8192;
#if HAVE_STRUCT_STATVFS_F_IOSIZE && HAVE_FSTATVFS
		warn("can't fstatvfs `%s', using default %d byte chunk",
		    image, bufsize);
	} else
		bufsize = sfs.f_iosize;
#endif
	bufrem = fsopts->size;
	if (fsopts->sparse) {
		if (ftruncate(fsopts->fd, bufrem) == -1) {
			warn("sparse option disabled.");
			fsopts->sparse = 0;
		}
	}
	if (fsopts->sparse) {
		/* File truncated at bufrem. Remaining is 0 */
		bufrem = 0;
		buf = NULL;
	} else {
		if (debug & DEBUG_FS_CREATE_IMAGE)
			printf("zero-ing image `%s', %lld sectors, "
			    "using %d byte chunks\n", image, (long long)bufrem,
			    bufsize);
		buf = ecalloc(1, bufsize);
	}

	if (fsopts->offset != 0)
		if (lseek(fsopts->fd, fsopts->offset, SEEK_SET) == -1) {
			warn("can't seek");
			free(buf);
			return -1;
		}

	while (bufrem > 0) {
		i = write(fsopts->fd, buf, MIN(bufsize, bufrem));
		if (i == -1) {
			warn("zeroing image, %lld bytes to go",
			    (long long)bufrem);
			free(buf);
			return (-1);
		}
		bufrem -= i;
	}
	if (buf)
		free(buf);

		/* make the file system */
	if (debug & DEBUG_FS_CREATE_IMAGE)
		printf("calling mkfs(\"%s\", ...)\n", image);

	if (stampst.st_ino != 0)
		tstamp = stampst.st_ctime;
	else
		tstamp = start_time.tv_sec;

	srandom(tstamp);

	fs = ffs_mkfs(image, fsopts, tstamp);
	fsopts->superblock = (void *)fs;
	if (debug & DEBUG_FS_CREATE_IMAGE) {
		time_t t;

		t = (time_t)((struct fs *)fsopts->superblock)->fs_time;
		printf("mkfs returned %p; fs_time %s",
		    fsopts->superblock, ctime(&t));
		printf("fs totals: nbfree %lld, nffree %lld, nifree %lld, ndir %lld\n",
		    (long long)fs->fs_cstotal.cs_nbfree,
		    (long long)fs->fs_cstotal.cs_nffree,
		    (long long)fs->fs_cstotal.cs_nifree,
		    (long long)fs->fs_cstotal.cs_ndir);
	}

	if (fs->fs_cstotal.cs_nifree + UFS_ROOTINO < fsopts->inodes) {
		warnx(
		"Image file `%s' has %lld free inodes; %lld are required.",
		    image,
		    (long long)(fs->fs_cstotal.cs_nifree + UFS_ROOTINO),
		    (long long)fsopts->inodes);
		return (-1);
	}
	return (fsopts->fd);
}