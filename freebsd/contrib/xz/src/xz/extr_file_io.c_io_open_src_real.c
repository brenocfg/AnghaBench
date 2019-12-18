#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ io_wait_ret ;
struct TYPE_7__ {int st_mode; int st_nlink; } ;
struct TYPE_6__ {scalar_t__ src_name; int src_fd; TYPE_2__ src_st; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 int const EFTYPE ; 
 int const EINTR ; 
 int const ELOOP ; 
 int const EMLINK ; 
 int const ENOTSUP ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ const IO_WAIT_MORE ; 
 scalar_t__ MODE_LIST ; 
 int O_BINARY ; 
 int O_NOCTTY ; 
 int O_NOFOLLOW ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  POSIX_FADV_RANDOM ; 
 int /*<<< orphan*/  POSIX_FADV_SEQUENTIAL ; 
 int STDIN_FILENO ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int const errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ fstat (int,TYPE_2__*) ; 
 scalar_t__ io_wait (TYPE_1__*,int,int) ; 
 scalar_t__ lstat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  message_error (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  message_warning (int /*<<< orphan*/ ,scalar_t__) ; 
 int open (scalar_t__,int) ; 
 scalar_t__ opt_force ; 
 scalar_t__ opt_mode ; 
 scalar_t__ opt_stdout ; 
 int /*<<< orphan*/  posix_fadvise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int restore_stdin_flags ; 
 int /*<<< orphan*/  setmode (int,int) ; 
 int /*<<< orphan*/  signals_block () ; 
 int /*<<< orphan*/  signals_unblock () ; 
 scalar_t__ stat (scalar_t__,TYPE_2__*) ; 
 scalar_t__ stdin_filename ; 
 int stdin_flags ; 
 int /*<<< orphan*/  strerror (int const) ; 

__attribute__((used)) static bool
io_open_src_real(file_pair *pair)
{
	// There's nothing to open when reading from stdin.
	if (pair->src_name == stdin_filename) {
		pair->src_fd = STDIN_FILENO;
#ifdef TUKLIB_DOSLIKE
		setmode(STDIN_FILENO, O_BINARY);
#else
		// Try to set stdin to non-blocking mode. It won't work
		// e.g. on OpenBSD if stdout is e.g. /dev/null. In such
		// case we proceed as if stdin were non-blocking anyway
		// (in case of /dev/null it will be in practice). The
		// same applies to stdout in io_open_dest_real().
		stdin_flags = fcntl(STDIN_FILENO, F_GETFL);
		if (stdin_flags == -1) {
			message_error(_("Error getting the file status flags "
					"from standard input: %s"),
					strerror(errno));
			return true;
		}

		if ((stdin_flags & O_NONBLOCK) == 0
				&& fcntl(STDIN_FILENO, F_SETFL,
					stdin_flags | O_NONBLOCK) != -1)
			restore_stdin_flags = true;
#endif
#ifdef HAVE_POSIX_FADVISE
		// It will fail if stdin is a pipe and that's fine.
		(void)posix_fadvise(STDIN_FILENO, 0, 0,
				opt_mode == MODE_LIST
					? POSIX_FADV_RANDOM
					: POSIX_FADV_SEQUENTIAL);
#endif
		return false;
	}

	// Symlinks are not followed unless writing to stdout or --force
	// was used.
	const bool follow_symlinks = opt_stdout || opt_force;

	// We accept only regular files if we are writing the output
	// to disk too. bzip2 allows overriding this with --force but
	// gzip and xz don't.
	const bool reg_files_only = !opt_stdout;

	// Flags for open()
	int flags = O_RDONLY | O_BINARY | O_NOCTTY;

#ifndef TUKLIB_DOSLIKE
	// Use non-blocking I/O:
	//   - It prevents blocking when opening FIFOs and some other
	//     special files, which is good if we want to accept only
	//     regular files.
	//   - It can help avoiding some race conditions with signal handling.
	flags |= O_NONBLOCK;
#endif

#if defined(O_NOFOLLOW)
	if (!follow_symlinks)
		flags |= O_NOFOLLOW;
#elif !defined(TUKLIB_DOSLIKE)
	// Some POSIX-like systems lack O_NOFOLLOW (it's not required
	// by POSIX). Check for symlinks with a separate lstat() on
	// these systems.
	if (!follow_symlinks) {
		struct stat st;
		if (lstat(pair->src_name, &st)) {
			message_error("%s: %s", pair->src_name,
					strerror(errno));
			return true;

		} else if (S_ISLNK(st.st_mode)) {
			message_warning(_("%s: Is a symbolic link, "
					"skipping"), pair->src_name);
			return true;
		}
	}
#else
	// Avoid warnings.
	(void)follow_symlinks;
#endif

	// Try to open the file. Signals have been blocked so EINTR shouldn't
	// be possible.
	pair->src_fd = open(pair->src_name, flags);

	if (pair->src_fd == -1) {
		// Signals (that have a signal handler) have been blocked.
		assert(errno != EINTR);

#ifdef O_NOFOLLOW
		// Give an understandable error message if the reason
		// for failing was that the file was a symbolic link.
		//
		// Note that at least Linux, OpenBSD, Solaris, and Darwin
		// use ELOOP to indicate that O_NOFOLLOW was the reason
		// that open() failed. Because there may be
		// directories in the pathname, ELOOP may occur also
		// because of a symlink loop in the directory part.
		// So ELOOP doesn't tell us what actually went wrong,
		// and this stupidity went into POSIX-1.2008 too.
		//
		// FreeBSD associates EMLINK with O_NOFOLLOW and
		// Tru64 uses ENOTSUP. We use these directly here
		// and skip the lstat() call and the associated race.
		// I want to hear if there are other kernels that
		// fail with something else than ELOOP with O_NOFOLLOW.
		bool was_symlink = false;

#	if defined(__FreeBSD__) || defined(__DragonFly__)
		if (errno == EMLINK)
			was_symlink = true;

#	elif defined(__digital__) && defined(__unix__)
		if (errno == ENOTSUP)
			was_symlink = true;

#	elif defined(__NetBSD__)
		if (errno == EFTYPE)
			was_symlink = true;

#	else
		if (errno == ELOOP && !follow_symlinks) {
			const int saved_errno = errno;
			struct stat st;
			if (lstat(pair->src_name, &st) == 0
					&& S_ISLNK(st.st_mode))
				was_symlink = true;

			errno = saved_errno;
		}
#	endif

		if (was_symlink)
			message_warning(_("%s: Is a symbolic link, "
					"skipping"), pair->src_name);
		else
#endif
			// Something else than O_NOFOLLOW failing
			// (assuming that the race conditions didn't
			// confuse us).
			message_error("%s: %s", pair->src_name,
					strerror(errno));

		return true;
	}

	// Stat the source file. We need the result also when we copy
	// the permissions, and when unlinking.
	//
	// NOTE: Use stat() instead of fstat() with DJGPP, because
	// then we have a better chance to get st_ino value that can
	// be used in io_open_dest_real() to prevent overwriting the
	// source file.
#ifdef __DJGPP__
	if (stat(pair->src_name, &pair->src_st))
		goto error_msg;
#else
	if (fstat(pair->src_fd, &pair->src_st))
		goto error_msg;
#endif

	if (S_ISDIR(pair->src_st.st_mode)) {
		message_warning(_("%s: Is a directory, skipping"),
				pair->src_name);
		goto error;
	}

	if (reg_files_only && !S_ISREG(pair->src_st.st_mode)) {
		message_warning(_("%s: Not a regular file, skipping"),
				pair->src_name);
		goto error;
	}

#ifndef TUKLIB_DOSLIKE
	if (reg_files_only && !opt_force) {
		if (pair->src_st.st_mode & (S_ISUID | S_ISGID)) {
			// gzip rejects setuid and setgid files even
			// when --force was used. bzip2 doesn't check
			// for them, but calls fchown() after fchmod(),
			// and many systems automatically drop setuid
			// and setgid bits there.
			//
			// We accept setuid and setgid files if
			// --force was used. We drop these bits
			// explicitly in io_copy_attr().
			message_warning(_("%s: File has setuid or "
					"setgid bit set, skipping"),
					pair->src_name);
			goto error;
		}

		if (pair->src_st.st_mode & S_ISVTX) {
			message_warning(_("%s: File has sticky bit "
					"set, skipping"),
					pair->src_name);
			goto error;
		}

		if (pair->src_st.st_nlink > 1) {
			message_warning(_("%s: Input file has more "
					"than one hard link, "
					"skipping"), pair->src_name);
			goto error;
		}
	}

	// If it is something else than a regular file, wait until
	// there is input available. This way reading from FIFOs
	// will work when open() is used with O_NONBLOCK.
	if (!S_ISREG(pair->src_st.st_mode)) {
		signals_unblock();
		const io_wait_ret ret = io_wait(pair, -1, true);
		signals_block();

		if (ret != IO_WAIT_MORE)
			goto error;
	}
#endif

#ifdef HAVE_POSIX_FADVISE
	// It will fail with some special files like FIFOs but that is fine.
	(void)posix_fadvise(pair->src_fd, 0, 0,
			opt_mode == MODE_LIST
				? POSIX_FADV_RANDOM
				: POSIX_FADV_SEQUENTIAL);
#endif

	return false;

error_msg:
	message_error("%s: %s", pair->src_name, strerror(errno));
error:
	(void)close(pair->src_fd);
	return true;
}