#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sftp_conn {int dummy; } ;
struct TYPE_5__ {int gl_matchc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  g ;

/* Variables and functions */
 int /*<<< orphan*/  GLOB_MARK ; 
 int GLOB_NOSPACE ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  debug3 (char*,char*) ; 
 int do_download (struct sftp_conn*,char*,char*,int /*<<< orphan*/ *,int,int,int) ; 
 int download_dir (struct sftp_conn*,char*,char*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int global_aflag ; 
 scalar_t__ global_fflag ; 
 scalar_t__ global_pflag ; 
 scalar_t__ global_rflag ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  interrupted ; 
 scalar_t__ is_dir (char const*) ; 
 char* make_absolute (char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mprintf (char*,char*,char*) ; 
 char* path_append (char const*,char*) ; 
 scalar_t__ pathname_is_dir (char*) ; 
 int /*<<< orphan*/  quiet ; 
 int remote_glob (struct sftp_conn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int
process_get(struct sftp_conn *conn, const char *src, const char *dst,
    const char *pwd, int pflag, int rflag, int resume, int fflag)
{
	char *abs_src = NULL;
	char *abs_dst = NULL;
	glob_t g;
	char *filename, *tmp=NULL;
	int i, r, err = 0;

	abs_src = xstrdup(src);
	abs_src = make_absolute(abs_src, pwd);
	memset(&g, 0, sizeof(g));

	debug3("Looking up %s", abs_src);
	if ((r = remote_glob(conn, abs_src, GLOB_MARK, NULL, &g)) != 0) {
		if (r == GLOB_NOSPACE) {
			error("Too many matches for \"%s\".", abs_src);
		} else {
			error("File \"%s\" not found.", abs_src);
		}
		err = -1;
		goto out;
	}

	/*
	 * If multiple matches then dst must be a directory or
	 * unspecified.
	 */
	if (g.gl_matchc > 1 && dst != NULL && !is_dir(dst)) {
		error("Multiple source paths, but destination "
		    "\"%s\" is not a directory", dst);
		err = -1;
		goto out;
	}

	for (i = 0; g.gl_pathv[i] && !interrupted; i++) {
		tmp = xstrdup(g.gl_pathv[i]);
		if ((filename = basename(tmp)) == NULL) {
			error("basename %s: %s", tmp, strerror(errno));
			free(tmp);
			err = -1;
			goto out;
		}

		if (g.gl_matchc == 1 && dst) {
			if (is_dir(dst)) {
				abs_dst = path_append(dst, filename);
			} else {
				abs_dst = xstrdup(dst);
			}
		} else if (dst) {
			abs_dst = path_append(dst, filename);
		} else {
			abs_dst = xstrdup(filename);
		}
		free(tmp);

		resume |= global_aflag;
		if (!quiet && resume)
			mprintf("Resuming %s to %s\n",
			    g.gl_pathv[i], abs_dst);
		else if (!quiet && !resume)
			mprintf("Fetching %s to %s\n",
			    g.gl_pathv[i], abs_dst);
		if (pathname_is_dir(g.gl_pathv[i]) && (rflag || global_rflag)) {
			if (download_dir(conn, g.gl_pathv[i], abs_dst, NULL,
			    pflag || global_pflag, 1, resume,
			    fflag || global_fflag) == -1)
				err = -1;
		} else {
			if (do_download(conn, g.gl_pathv[i], abs_dst, NULL,
			    pflag || global_pflag, resume,
			    fflag || global_fflag) == -1)
				err = -1;
		}
		free(abs_dst);
		abs_dst = NULL;
	}

out:
	free(abs_src);
	globfree(&g);
	return(err);
}