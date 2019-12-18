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
typedef  int /*<<< orphan*/  file_path ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  dir_path ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PERM_DIR ; 
 int /*<<< orphan*/  PERM_FILE ; 
 int aio_present ; 
 int /*<<< orphan*/  aio_read_wrapper ; 
 int /*<<< orphan*/  aio_write_wrapper ; 
 int /*<<< orphan*/  check_directory_open_modes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_dup (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_dup2 (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fchdir (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fchflags (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fchmod (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fchown (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_flock (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fpathconf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fstat (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fstatfs (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fsync (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ftruncate (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_futimes (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_getdents (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_lseek (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mmap_exec (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mmap_read (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mmap_write (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mmap_write_private (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_read (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_sendfile (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_write (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dir_modes ; 
 int /*<<< orphan*/  dir_modes_count ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_modes ; 
 int /*<<< orphan*/  file_modes_count ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  pread_wrapper ; 
 int /*<<< orphan*/  preadv_wrapper ; 
 int /*<<< orphan*/  pwrite_wrapper ; 
 int /*<<< orphan*/  pwritev_wrapper ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  readv_wrapper ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  write ; 
 int /*<<< orphan*/  writev_wrapper ; 

int
main(void)
{
	char dir_path[PATH_MAX], file_path[PATH_MAX];
	int dummy, fd;
	size_t size;

	aio_present = 0;
	size = sizeof(dummy);
	if (sysctlbyname("vfs.aio", &dummy, &size, NULL, 0) < 0) {
		if (errno == EISDIR)
			aio_present = 1;
	}

	strlcpy(dir_path, "/tmp/open-dir.XXXXXXXXXXX", sizeof(dir_path));
	if (mkdtemp(dir_path) == NULL)
		err(1, "mkdtemp");
	if (chmod(dir_path, PERM_DIR) < 0) {
		warn("chmod %s", dir_path);
		(void)rmdir(dir_path);
		exit(1);
	}
	strlcpy(file_path, "/tmp/open-file.XXXXXXXXXXX", sizeof(file_path));
	fd = mkstemp(file_path);
	if (fd < 0) {
		warn("mkstemp");
		(void)rmdir(dir_path);
		exit(1);
	}
	close(fd);
	if (chmod(file_path, PERM_FILE) < 0) {
		warn("chmod %s", file_path);
		(void)unlink(file_path);
		(void)rmdir(dir_path);
		exit(1);
	}
	check_directory_open_modes(dir_path, file_modes, file_modes_count);

	check_dup("check_dup_dir", dir_path, dir_modes, dir_modes_count);
	check_dup("check_dup_file", file_path, file_modes, file_modes_count);

	check_dup2("check_dup2_dir", dir_path, dir_modes, dir_modes_count);
	check_dup2("check_dup2_file", file_path, file_modes,
	    file_modes_count);

	check_fchdir("check_fchdir", dir_path, dir_modes, dir_modes_count);

	check_fchflags("check_fchflags_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_fchflags("check_fchflags_file", file_path, file_modes,
	    file_modes_count);

	check_fchmod("check_fchmod_dir", dir_path, PERM_DIR, dir_modes,
	    dir_modes_count);
	check_fchmod("check_fchmod_file", file_path, PERM_FILE, file_modes,
	    file_modes_count);

	check_fchown("check_fchown_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_fchown("check_fchown_file", file_path, file_modes,
	    file_modes_count);

	check_flock("check_flock_dir", dir_path, dir_modes, dir_modes_count);
	check_flock("check_flock_file", file_path, file_modes,
	    file_modes_count);

	check_fpathconf("check_fpathconf_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_fpathconf("check_fpathconf_file", file_path, file_modes,
	    file_modes_count);

	check_fstat("check_fstat_dir", dir_path, dir_modes, dir_modes_count);
	check_fstat("check_fstat_file", file_path, file_modes,
	    file_modes_count);

	check_fstatfs("check_fstatfs_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_fstatfs("check_fstatfs_file", file_path, file_modes,
	    file_modes_count);

	check_fsync("check_fsync_dir", dir_path, dir_modes, dir_modes_count);
	check_fsync("check_fsync_file", file_path, file_modes,
	    file_modes_count);

	check_ftruncate("check_ftruncate_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_ftruncate("check_ftruncate_file", file_path, file_modes,
	    file_modes_count);

	check_futimes("check_futimes_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_futimes("check_futimes_file", file_path, file_modes,
	    file_modes_count);

	check_lseek("check_lseek_dir", dir_path, dir_modes, dir_modes_count);
	check_lseek("check_lseek_file", file_path, file_modes,
	    file_modes_count);

	check_getdents("check_getdents_dir", dir_path, 1, dir_modes,
	    dir_modes_count);
	check_getdents("check_getdents_file", file_path, 0, file_modes,
	    file_modes_count);

	check_sendfile("check_sendfile_dir", dir_path, 1, dir_modes,
	    dir_modes_count);
	check_sendfile("check_sendfile_file", file_path, 0, file_modes,
	    file_modes_count);

	check_write("check_write_dir", write, dir_path, dir_modes,
	    dir_modes_count);
	check_write("check_write_file", write, file_path, file_modes,
	    file_modes_count);

	check_write("check_writev_dir", writev_wrapper, dir_path, dir_modes,
	    dir_modes_count);
	check_write("check_writev_file", writev_wrapper, file_path,
	    file_modes, file_modes_count);

	check_write("check_pwrite_dir", pwrite_wrapper, dir_path, dir_modes,
	    dir_modes_count);
	check_write("check_pwrite_file", pwrite_wrapper, file_path,
	    file_modes, file_modes_count);

	check_write("check_pwritev_dir", pwritev_wrapper, dir_path,
	    dir_modes, dir_modes_count);
	check_write("check_pwritev_file", pwritev_wrapper, file_path,
	    file_modes, file_modes_count);

	if (aio_present) {
		check_write("check_aio_write_dir", aio_write_wrapper,
		    dir_path, dir_modes, dir_modes_count);
		check_write("check_aio_write_file", aio_write_wrapper,
		    file_path, file_modes, file_modes_count);
	}

	check_read("check_read_dir", read, dir_path, dir_modes,
	    dir_modes_count);
	check_read("check_read_file", read, file_path, file_modes,
	    file_modes_count);

	check_read("check_readv_dir", readv_wrapper, dir_path, dir_modes,
	    dir_modes_count);
	check_read("check_readv_file", readv_wrapper, file_path,
	    file_modes, file_modes_count);

	check_read("check_pread_dir", pread_wrapper, dir_path, dir_modes,
	    dir_modes_count);
	check_read("check_pread_file", pread_wrapper, file_path,
	    file_modes, file_modes_count);

	check_read("check_preadv_dir", preadv_wrapper, dir_path,
	    dir_modes, dir_modes_count);
	check_read("check_preadv_file", preadv_wrapper, file_path,
	    file_modes, file_modes_count);

	if (aio_present) {
		check_read("check_aio_read_dir", aio_read_wrapper, dir_path,
		    dir_modes, dir_modes_count);
		check_read("check_aio_read_file", aio_read_wrapper,
		    file_path, file_modes, file_modes_count);
	}

	check_mmap_read("check_mmap_read_dir", dir_path, 1, dir_modes,
	    dir_modes_count);
	check_mmap_read("check_mmap_read_file", file_path, 0, file_modes,
	    file_modes_count);

	check_mmap_write("check_mmap_write_dir", dir_path, dir_modes,
	    dir_modes_count);
	check_mmap_write("check_mmap_write_file", file_path, file_modes,
	    file_modes_count);

	check_mmap_exec("check_mmap_exec_dir", dir_path, 1, dir_modes,
	    dir_modes_count);
	check_mmap_exec("check_mmap_exec_file", file_path, 0, file_modes,
	    file_modes_count);

	check_mmap_write_private("check_mmap_write_private_dir", dir_path, 1,
	    dir_modes, dir_modes_count);
	check_mmap_write_private("check_mmap_write_private_file", file_path,
	    0, file_modes, file_modes_count);

	(void)unlink(file_path);
	(void)rmdir(dir_path);
	exit(0);
}