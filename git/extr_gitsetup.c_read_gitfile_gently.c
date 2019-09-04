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
struct stat {int const st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int READ_GITFILE_ERR_INVALID_FORMAT ; 
 int READ_GITFILE_ERR_NOT_A_FILE ; 
 int READ_GITFILE_ERR_NOT_A_REPO ; 
 int READ_GITFILE_ERR_NO_PATH ; 
 int READ_GITFILE_ERR_OPEN_FAILED ; 
 int READ_GITFILE_ERR_READ_FAILED ; 
 int READ_GITFILE_ERR_STAT_FAILED ; 
 int READ_GITFILE_ERR_TOO_LARGE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 int /*<<< orphan*/  is_git_directory (char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_gitfile_error_die (int,char const*,char*) ; 
 int read_in_full (int,char*,int const) ; 
 char* real_path (char*) ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 char* strrchr (char const*,char) ; 
 char* xmallocz (int const) ; 
 char* xstrfmt (char*,int,char const*,int,char*) ; 

const char *read_gitfile_gently(const char *path, int *return_error_code)
{
	const int max_file_size = 1 << 20;  /* 1MB */
	int error_code = 0;
	char *buf = NULL;
	char *dir = NULL;
	const char *slash;
	struct stat st;
	int fd;
	ssize_t len;

	if (stat(path, &st)) {
		/* NEEDSWORK: discern between ENOENT vs other errors */
		error_code = READ_GITFILE_ERR_STAT_FAILED;
		goto cleanup_return;
	}
	if (!S_ISREG(st.st_mode)) {
		error_code = READ_GITFILE_ERR_NOT_A_FILE;
		goto cleanup_return;
	}
	if (st.st_size > max_file_size) {
		error_code = READ_GITFILE_ERR_TOO_LARGE;
		goto cleanup_return;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		error_code = READ_GITFILE_ERR_OPEN_FAILED;
		goto cleanup_return;
	}
	buf = xmallocz(st.st_size);
	len = read_in_full(fd, buf, st.st_size);
	close(fd);
	if (len != st.st_size) {
		error_code = READ_GITFILE_ERR_READ_FAILED;
		goto cleanup_return;
	}
	if (!starts_with(buf, "gitdir: ")) {
		error_code = READ_GITFILE_ERR_INVALID_FORMAT;
		goto cleanup_return;
	}
	while (buf[len - 1] == '\n' || buf[len - 1] == '\r')
		len--;
	if (len < 9) {
		error_code = READ_GITFILE_ERR_NO_PATH;
		goto cleanup_return;
	}
	buf[len] = '\0';
	dir = buf + 8;

	if (!is_absolute_path(dir) && (slash = strrchr(path, '/'))) {
		size_t pathlen = slash+1 - path;
		dir = xstrfmt("%.*s%.*s", (int)pathlen, path,
			      (int)(len - 8), buf + 8);
		free(buf);
		buf = dir;
	}
	if (!is_git_directory(dir)) {
		error_code = READ_GITFILE_ERR_NOT_A_REPO;
		goto cleanup_return;
	}
	path = real_path(dir);

cleanup_return:
	if (return_error_code)
		*return_error_code = error_code;
	else if (error_code)
		read_gitfile_error_die(error_code, path, dir);

	free(buf);
	return error_code ? NULL : path;
}