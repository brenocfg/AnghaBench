#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct sftp_conn {int dummy; } ;
struct dirent {scalar_t__ d_ino; char* d_name; } ;
struct TYPE_7__ {int perm; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  TYPE_1__ Attrib ;

/* Variables and functions */
 int MAX_DIR_DEPTH ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_ACMODTIME ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_SIZE ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_UIDGID ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  attrib_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ do_mkdir (struct sftp_conn*,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_setstat (struct sftp_conn*,char const*,TYPE_1__*) ; 
 TYPE_1__* do_stat (struct sftp_conn*,char const*,int /*<<< orphan*/ ) ; 
 int do_upload (struct sftp_conn*,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  interrupted ; 
 int /*<<< orphan*/  logit (char*,char*,...) ; 
 int lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  mprintf (char*,char const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 char* path_append (char const*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stat_to_attrib (struct stat*,TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upload_dir_internal(struct sftp_conn *conn, const char *src, const char *dst,
    int depth, int preserve_flag, int print_flag, int resume, int fsync_flag)
{
	int ret = 0;
	DIR *dirp;
	struct dirent *dp;
	char *filename, *new_src = NULL, *new_dst = NULL;
	struct stat sb;
	Attrib a, *dirattrib;

	if (depth >= MAX_DIR_DEPTH) {
		error("Maximum directory depth exceeded: %d levels", depth);
		return -1;
	}

	if (stat(src, &sb) == -1) {
		error("Couldn't stat directory \"%s\": %s",
		    src, strerror(errno));
		return -1;
	}
	if (!S_ISDIR(sb.st_mode)) {
		error("\"%s\" is not a directory", src);
		return -1;
	}
	if (print_flag)
		mprintf("Entering %s\n", src);

	attrib_clear(&a);
	stat_to_attrib(&sb, &a);
	a.flags &= ~SSH2_FILEXFER_ATTR_SIZE;
	a.flags &= ~SSH2_FILEXFER_ATTR_UIDGID;
	a.perm &= 01777;
	if (!preserve_flag)
		a.flags &= ~SSH2_FILEXFER_ATTR_ACMODTIME;

	/*
	 * sftp lacks a portable status value to match errno EEXIST,
	 * so if we get a failure back then we must check whether
	 * the path already existed and is a directory.
	 */
	if (do_mkdir(conn, dst, &a, 0) != 0) {
		if ((dirattrib = do_stat(conn, dst, 0)) == NULL)
			return -1;
		if (!S_ISDIR(dirattrib->perm)) {
			error("\"%s\" exists but is not a directory", dst);
			return -1;
		}
	}

	if ((dirp = opendir(src)) == NULL) {
		error("Failed to open dir \"%s\": %s", src, strerror(errno));
		return -1;
	}

	while (((dp = readdir(dirp)) != NULL) && !interrupted) {
		if (dp->d_ino == 0)
			continue;
		free(new_dst);
		free(new_src);
		filename = dp->d_name;
		new_dst = path_append(dst, filename);
		new_src = path_append(src, filename);

		if (lstat(new_src, &sb) == -1) {
			logit("%s: lstat failed: %s", filename,
			    strerror(errno));
			ret = -1;
		} else if (S_ISDIR(sb.st_mode)) {
			if (strcmp(filename, ".") == 0 ||
			    strcmp(filename, "..") == 0)
				continue;

			if (upload_dir_internal(conn, new_src, new_dst,
			    depth + 1, preserve_flag, print_flag, resume,
			    fsync_flag) == -1)
				ret = -1;
		} else if (S_ISREG(sb.st_mode)) {
			if (do_upload(conn, new_src, new_dst,
			    preserve_flag, resume, fsync_flag) == -1) {
				error("Uploading of file %s to %s failed!",
				    new_src, new_dst);
				ret = -1;
			}
		} else
			logit("%s: not a regular file\n", filename);
	}
	free(new_dst);
	free(new_src);

	do_setstat(conn, dst, &a);

	(void) closedir(dirp);
	return ret;
}