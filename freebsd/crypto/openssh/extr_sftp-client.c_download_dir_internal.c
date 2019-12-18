#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sftp_conn {int dummy; } ;
typedef  int mode_t ;
struct TYPE_9__ {int perm; int flags; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct TYPE_8__ {char* filename; TYPE_2__ a; } ;
typedef  TYPE_1__ SFTP_DIRENT ;
typedef  TYPE_2__ Attrib ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int MAX_DIR_DEPTH ; 
 int SSH2_FILEXFER_ATTR_ACMODTIME ; 
 int SSH2_FILEXFER_ATTR_PERMISSIONS ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  debug (char*,char const*) ; 
 int do_download (struct sftp_conn*,char*,char*,TYPE_2__*,int,int,int) ; 
 int do_readdir (struct sftp_conn*,char const*,TYPE_1__***) ; 
 TYPE_2__* do_stat (struct sftp_conn*,char const*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_sftp_dirents (TYPE_1__**) ; 
 int /*<<< orphan*/  interrupted ; 
 int /*<<< orphan*/  logit (char*,char*) ; 
 int mkdir (char const*,int) ; 
 int /*<<< orphan*/  mprintf (char*,char const*) ; 
 char* path_append (char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (scalar_t__) ; 
 int utimes (char const*,struct timeval*) ; 

__attribute__((used)) static int
download_dir_internal(struct sftp_conn *conn, const char *src, const char *dst,
    int depth, Attrib *dirattrib, int preserve_flag, int print_flag,
    int resume_flag, int fsync_flag)
{
	int i, ret = 0;
	SFTP_DIRENT **dir_entries;
	char *filename, *new_src = NULL, *new_dst = NULL;
	mode_t mode = 0777;

	if (depth >= MAX_DIR_DEPTH) {
		error("Maximum directory depth exceeded: %d levels", depth);
		return -1;
	}

	if (dirattrib == NULL &&
	    (dirattrib = do_stat(conn, src, 1)) == NULL) {
		error("Unable to stat remote directory \"%s\"", src);
		return -1;
	}
	if (!S_ISDIR(dirattrib->perm)) {
		error("\"%s\" is not a directory", src);
		return -1;
	}
	if (print_flag)
		mprintf("Retrieving %s\n", src);

	if (dirattrib->flags & SSH2_FILEXFER_ATTR_PERMISSIONS)
		mode = dirattrib->perm & 01777;
	else {
		debug("Server did not send permissions for "
		    "directory \"%s\"", dst);
	}

	if (mkdir(dst, mode) == -1 && errno != EEXIST) {
		error("mkdir %s: %s", dst, strerror(errno));
		return -1;
	}

	if (do_readdir(conn, src, &dir_entries) == -1) {
		error("%s: Failed to get directory contents", src);
		return -1;
	}

	for (i = 0; dir_entries[i] != NULL && !interrupted; i++) {
		free(new_dst);
		free(new_src);

		filename = dir_entries[i]->filename;
		new_dst = path_append(dst, filename);
		new_src = path_append(src, filename);

		if (S_ISDIR(dir_entries[i]->a.perm)) {
			if (strcmp(filename, ".") == 0 ||
			    strcmp(filename, "..") == 0)
				continue;
			if (download_dir_internal(conn, new_src, new_dst,
			    depth + 1, &(dir_entries[i]->a), preserve_flag,
			    print_flag, resume_flag, fsync_flag) == -1)
				ret = -1;
		} else if (S_ISREG(dir_entries[i]->a.perm) ) {
			if (do_download(conn, new_src, new_dst,
			    &(dir_entries[i]->a), preserve_flag,
			    resume_flag, fsync_flag) == -1) {
				error("Download of file %s to %s failed",
				    new_src, new_dst);
				ret = -1;
			}
		} else
			logit("%s: not a regular file\n", new_src);

	}
	free(new_dst);
	free(new_src);

	if (preserve_flag) {
		if (dirattrib->flags & SSH2_FILEXFER_ATTR_ACMODTIME) {
			struct timeval tv[2];
			tv[0].tv_sec = dirattrib->atime;
			tv[1].tv_sec = dirattrib->mtime;
			tv[0].tv_usec = tv[1].tv_usec = 0;
			if (utimes(dst, tv) == -1)
				error("Can't set times on \"%s\": %s",
				    dst, strerror(errno));
		} else
			debug("Server did not send times for directory "
			    "\"%s\"", dst);
	}

	free_sftp_dirents(dir_entries);

	return ret;
}