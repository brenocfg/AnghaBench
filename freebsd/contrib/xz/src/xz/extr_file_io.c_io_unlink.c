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
struct stat {scalar_t__ st_ino; scalar_t__ st_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int lstat (char const*,struct stat*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ opt_force ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static void
io_unlink(const char *name, const struct stat *known_st)
{
#if defined(TUKLIB_DOSLIKE)
	// On DOS-like systems, st_ino is meaningless, so don't bother
	// testing it. Just silence a compiler warning.
	(void)known_st;
#else
	struct stat new_st;

	// If --force was used, use stat() instead of lstat(). This way
	// (de)compressing symlinks works correctly. However, it also means
	// that xz cannot detect if a regular file foo is renamed to bar
	// and then a symlink foo -> bar is created. Because of stat()
	// instead of lstat(), xz will think that foo hasn't been replaced
	// with another file. Thus, xz will remove foo even though it no
	// longer is the same file that xz used when it started compressing.
	// Probably it's not too bad though, so this doesn't need a more
	// complex fix.
	const int stat_ret = opt_force
			? stat(name, &new_st) : lstat(name, &new_st);

	if (stat_ret
#	ifdef __VMS
			// st_ino is an array, and we don't want to
			// compare st_dev at all.
			|| memcmp(&new_st.st_ino, &known_st->st_ino,
				sizeof(new_st.st_ino)) != 0
#	else
			// Typical POSIX-like system
			|| new_st.st_dev != known_st->st_dev
			|| new_st.st_ino != known_st->st_ino
#	endif
			)
		// TRANSLATORS: When compression or decompression finishes,
		// and xz is going to remove the source file, xz first checks
		// if the source file still exists, and if it does, does its
		// device and inode numbers match what xz saw when it opened
		// the source file. If these checks fail, this message is
		// shown, %s being the filename, and the file is not deleted.
		// The check for device and inode numbers is there, because
		// it is possible that the user has put a new file in place
		// of the original file, and in that case it obviously
		// shouldn't be removed.
		message_error(_("%s: File seems to have been moved, "
				"not removing"), name);
	else
#endif
		// There's a race condition between lstat() and unlink()
		// but at least we have tried to avoid removing wrong file.
		if (unlink(name))
			message_error(_("%s: Cannot remove: %s"),
					name, strerror(errno));

	return;
}