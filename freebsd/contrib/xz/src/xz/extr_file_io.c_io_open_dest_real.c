#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_dev; scalar_t__ st_ino; } ;
typedef  int mode_t ;
struct TYPE_7__ {int st_size; int /*<<< orphan*/  st_mode; scalar_t__* st_ino; scalar_t__ st_dev; } ;
struct TYPE_5__ {int st_dev; scalar_t__ st_ino; } ;
struct TYPE_6__ {scalar_t__ src_fd; char* dest_name; int dest_fd; int dest_try_sparse; TYPE_4__ dest_st; TYPE_1__ src_st; int /*<<< orphan*/  src_name; } ;
typedef  TYPE_2__ file_pair ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ MODE_DECOMPRESS ; 
 int O_APPEND ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOCTTY ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int S_IWUSR ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,TYPE_4__*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_error (char*,char*,...) ; 
 int open (char*,int,int const) ; 
 scalar_t__ opt_force ; 
 scalar_t__ opt_mode ; 
 scalar_t__ opt_stdout ; 
 int restore_stdout_flags ; 
 int /*<<< orphan*/  setmode (int,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int stdout_flags ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 char* suffix_get_dest_name (int /*<<< orphan*/ ) ; 
 scalar_t__ try_sparse ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static bool
io_open_dest_real(file_pair *pair)
{
	if (opt_stdout || pair->src_fd == STDIN_FILENO) {
		// We don't modify or free() this.
		pair->dest_name = (char *)"(stdout)";
		pair->dest_fd = STDOUT_FILENO;
#ifdef TUKLIB_DOSLIKE
		setmode(STDOUT_FILENO, O_BINARY);
#else
		// Try to set O_NONBLOCK if it isn't already set.
		// If it fails, we assume that stdout is non-blocking
		// in practice. See the comments in io_open_src_real()
		// for similar situation with stdin.
		//
		// NOTE: O_APPEND may be unset later in this function
		// and it relies on stdout_flags being set here.
		stdout_flags = fcntl(STDOUT_FILENO, F_GETFL);
		if (stdout_flags == -1) {
			message_error(_("Error getting the file status flags "
					"from standard output: %s"),
					strerror(errno));
			return true;
		}

		if ((stdout_flags & O_NONBLOCK) == 0
				&& fcntl(STDOUT_FILENO, F_SETFL,
					stdout_flags | O_NONBLOCK) != -1)
				restore_stdout_flags = true;
#endif
	} else {
		pair->dest_name = suffix_get_dest_name(pair->src_name);
		if (pair->dest_name == NULL)
			return true;

#ifdef __DJGPP__
		struct stat st;
		if (stat(pair->dest_name, &st) == 0) {
			// Check that it isn't a special file like "prn".
			if (st.st_dev == -1) {
				message_error("%s: Refusing to write to "
						"a DOS special file",
						pair->dest_name);
				free(pair->dest_name);
				return true;
			}

			// Check that we aren't overwriting the source file.
			if (st.st_dev == pair->src_st.st_dev
					&& st.st_ino == pair->src_st.st_ino) {
				message_error("%s: Output file is the same "
						"as the input file",
						pair->dest_name);
				free(pair->dest_name);
				return true;
			}
		}
#endif

		// If --force was used, unlink the target file first.
		if (opt_force && unlink(pair->dest_name) && errno != ENOENT) {
			message_error(_("%s: Cannot remove: %s"),
					pair->dest_name, strerror(errno));
			free(pair->dest_name);
			return true;
		}

		// Open the file.
		int flags = O_WRONLY | O_BINARY | O_NOCTTY
				| O_CREAT | O_EXCL;
#ifndef TUKLIB_DOSLIKE
		flags |= O_NONBLOCK;
#endif
		const mode_t mode = S_IRUSR | S_IWUSR;
		pair->dest_fd = open(pair->dest_name, flags, mode);

		if (pair->dest_fd == -1) {
			message_error("%s: %s", pair->dest_name,
					strerror(errno));
			free(pair->dest_name);
			return true;
		}
	}

#ifndef TUKLIB_DOSLIKE
	// dest_st isn't used on DOS-like systems except as a dummy
	// argument to io_unlink(), so don't fstat() on such systems.
	if (fstat(pair->dest_fd, &pair->dest_st)) {
		// If fstat() really fails, we have a safe fallback here.
#	if defined(__VMS)
		pair->dest_st.st_ino[0] = 0;
		pair->dest_st.st_ino[1] = 0;
		pair->dest_st.st_ino[2] = 0;
#	else
		pair->dest_st.st_dev = 0;
		pair->dest_st.st_ino = 0;
#	endif
	} else if (try_sparse && opt_mode == MODE_DECOMPRESS) {
		// When writing to standard output, we need to be extra
		// careful:
		//  - It may be connected to something else than
		//    a regular file.
		//  - We aren't necessarily writing to a new empty file
		//    or to the end of an existing file.
		//  - O_APPEND may be active.
		//
		// TODO: I'm keeping this disabled for DOS-like systems
		// for now. FAT doesn't support sparse files, but NTFS
		// does, so maybe this should be enabled on Windows after
		// some testing.
		if (pair->dest_fd == STDOUT_FILENO) {
			if (!S_ISREG(pair->dest_st.st_mode))
				return false;

			if (stdout_flags & O_APPEND) {
				// Creating a sparse file is not possible
				// when O_APPEND is active (it's used by
				// shell's >> redirection). As I understand
				// it, it is safe to temporarily disable
				// O_APPEND in xz, because if someone
				// happened to write to the same file at the
				// same time, results would be bad anyway
				// (users shouldn't assume that xz uses any
				// specific block size when writing data).
				//
				// The write position may be something else
				// than the end of the file, so we must fix
				// it to start writing at the end of the file
				// to imitate O_APPEND.
				if (lseek(STDOUT_FILENO, 0, SEEK_END) == -1)
					return false;

				// Construct the new file status flags.
				// If O_NONBLOCK was set earlier in this
				// function, it must be kept here too.
				int flags = stdout_flags & ~O_APPEND;
				if (restore_stdout_flags)
					flags |= O_NONBLOCK;

				// If this fcntl() fails, we continue but won't
				// try to create sparse output. The original
				// flags will still be restored if needed (to
				// unset O_NONBLOCK) when the file is finished.
				if (fcntl(STDOUT_FILENO, F_SETFL, flags) == -1)
					return false;

				// Disabling O_APPEND succeeded. Mark
				// that the flags should be restored
				// in io_close_dest(). (This may have already
				// been set when enabling O_NONBLOCK.)
				restore_stdout_flags = true;

			} else if (lseek(STDOUT_FILENO, 0, SEEK_CUR)
					!= pair->dest_st.st_size) {
				// Writing won't start exactly at the end
				// of the file. We cannot use sparse output,
				// because it would probably corrupt the file.
				return false;
			}
		}

		pair->dest_try_sparse = true;
	}
#endif

	return false;
}