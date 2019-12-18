#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const wchar_t ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_3__ {char* m; int /*<<< orphan*/  const* w; } ;
struct read_file_data {scalar_t__ filename_type; size_t block_size; int fd; int use_lseek; int /*<<< orphan*/  st_mode; void* buffer; TYPE_1__ filename; } ;
typedef  scalar_t__ partinfo ;
typedef  scalar_t__ disklabel ;
struct archive {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ p_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  DIOCGDINFO ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGPART ; 
 size_t DISKPART (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FNT_MBS ; 
 scalar_t__ FNT_STDIN ; 
 scalar_t__ FNT_WCS ; 
 int O_BINARY ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (int) ; 
 int /*<<< orphan*/  const* __la_win_permissive_name_w (int /*<<< orphan*/  const*) ; 
 int _wopen (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  archive_clear_error (struct archive*) ; 
 int /*<<< orphan*/  archive_read_extract_set_skip_file (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
file_open(struct archive *a, void *client_data)
{
	struct stat st;
	struct read_file_data *mine = (struct read_file_data *)client_data;
	void *buffer;
	const char *filename = NULL;
	const wchar_t *wfilename = NULL;
	int fd = -1;
	int is_disk_like = 0;
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	off_t mediasize = 0; /* FreeBSD-specific, so off_t okay here. */
#elif defined(__NetBSD__) || defined(__OpenBSD__)
	struct disklabel dl;
#elif defined(__DragonFly__)
	struct partinfo pi;
#endif

	archive_clear_error(a);
	if (mine->filename_type == FNT_STDIN) {
		/* We used to delegate stdin support by
		 * directly calling archive_read_open_fd(a,0,block_size)
		 * here, but that doesn't (and shouldn't) handle the
		 * end-of-file flush when reading stdout from a pipe.
		 * Basically, read_open_fd() is intended for folks who
		 * are willing to handle such details themselves.  This
		 * API is intended to be a little smarter for folks who
		 * want easy handling of the common case.
		 */
		fd = 0;
#if defined(__CYGWIN__) || defined(_WIN32)
		setmode(0, O_BINARY);
#endif
		filename = "";
	} else if (mine->filename_type == FNT_MBS) {
		filename = mine->filename.m;
		fd = open(filename, O_RDONLY | O_BINARY | O_CLOEXEC);
		__archive_ensure_cloexec_flag(fd);
		if (fd < 0) {
			archive_set_error(a, errno,
			    "Failed to open '%s'", filename);
			return (ARCHIVE_FATAL);
		}
	} else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		wfilename = mine->filename.w;
		fd = _wopen(wfilename, O_RDONLY | O_BINARY);
		if (fd < 0 && errno == ENOENT) {
			wchar_t *fullpath;
			fullpath = __la_win_permissive_name_w(wfilename);
			if (fullpath != NULL) {
				fd = _wopen(fullpath, O_RDONLY | O_BINARY);
				free(fullpath);
			}
		}
		if (fd < 0) {
			archive_set_error(a, errno,
			    "Failed to open '%S'", wfilename);
			return (ARCHIVE_FATAL);
		}
#else
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Unexpedted operation in archive_read_open_filename");
		goto fail;
#endif
	}
	if (fstat(fd, &st) != 0) {
		if (mine->filename_type == FNT_WCS)
			archive_set_error(a, errno, "Can't stat '%S'",
			    wfilename);
		else
			archive_set_error(a, errno, "Can't stat '%s'",
			    filename);
		goto fail;
	}

	/*
	 * Determine whether the input looks like a disk device or a
	 * tape device.  The results are used below to select an I/O
	 * strategy:
	 *  = "disk-like" devices support arbitrary lseek() and will
	 *    support I/O requests of any size.  So we get easy skipping
	 *    and can cheat on block sizes to get better performance.
	 *  = "tape-like" devices require strict blocking and use
	 *    specialized ioctls for seeking.
	 *  = "socket-like" devices cannot seek at all but can improve
	 *    performance by using nonblocking I/O to read "whatever is
	 *    available right now".
	 *
	 * Right now, we only specially recognize disk-like devices,
	 * but it should be straightforward to add probes and strategy
	 * here for tape-like and socket-like devices.
	 */
	if (S_ISREG(st.st_mode)) {
		/* Safety:  Tell the extractor not to overwrite the input. */
		archive_read_extract_set_skip_file(a, st.st_dev, st.st_ino);
		/* Regular files act like disks. */
		is_disk_like = 1;
	}
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	/* FreeBSD: if it supports DIOCGMEDIASIZE ioctl, it's disk-like. */
	else if (S_ISCHR(st.st_mode) &&
	    ioctl(fd, DIOCGMEDIASIZE, &mediasize) == 0 &&
	    mediasize > 0) {
		is_disk_like = 1;
	}
#elif defined(__NetBSD__) || defined(__OpenBSD__)
	/* Net/OpenBSD: if it supports DIOCGDINFO ioctl, it's disk-like. */
	else if ((S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) &&
	    ioctl(fd, DIOCGDINFO, &dl) == 0 &&
	    dl.d_partitions[DISKPART(st.st_rdev)].p_size > 0) {
		is_disk_like = 1;
	}
#elif defined(__DragonFly__)
	/* DragonFly BSD:  if it supports DIOCGPART ioctl, it's disk-like. */
	else if (S_ISCHR(st.st_mode) &&
	    ioctl(fd, DIOCGPART, &pi) == 0 &&
	    pi.media_size > 0) {
		is_disk_like = 1;
	}
#elif defined(__linux__)
	/* Linux:  All block devices are disk-like. */
	else if (S_ISBLK(st.st_mode) &&
	    lseek(fd, 0, SEEK_CUR) == 0 &&
	    lseek(fd, 0, SEEK_SET) == 0 &&
	    lseek(fd, 0, SEEK_END) > 0 &&
	    lseek(fd, 0, SEEK_SET) == 0) {
		is_disk_like = 1;
	}
#endif
	/* TODO: Add an "is_tape_like" variable and appropriate tests. */

	/* Disk-like devices prefer power-of-two block sizes.  */
	/* Use provided block_size as a guide so users have some control. */
	if (is_disk_like) {
		size_t new_block_size = 64 * 1024;
		while (new_block_size < mine->block_size
		    && new_block_size < 64 * 1024 * 1024)
			new_block_size *= 2;
		mine->block_size = new_block_size;
	}
	buffer = malloc(mine->block_size);
	if (buffer == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		goto fail;
	}
	mine->buffer = buffer;
	mine->fd = fd;
	/* Remember mode so close can decide whether to flush. */
	mine->st_mode = st.st_mode;

	/* Disk-like inputs can use lseek(). */
	if (is_disk_like)
		mine->use_lseek = 1;

	return (ARCHIVE_OK);
fail:
	/*
	 * Don't close file descriptors not opened or ones pointing referring
	 * to `FNT_STDIN`.
	 */
	if (fd != -1 && fd != 0)
		close(fd);
	return (ARCHIVE_FATAL);
}