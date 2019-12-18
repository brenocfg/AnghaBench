#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  path_buf ;
struct TYPE_10__ {char** gl_pathv; scalar_t__ gl_pathc; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  g ;
struct TYPE_11__ {int flags; int perm; unsigned long uid; unsigned long gid; } ;
typedef  TYPE_2__ Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  GLOB_NOCHECK ; 
#define  I_CHDIR 154 
#define  I_CHGRP 153 
#define  I_CHMOD 152 
#define  I_CHOWN 151 
#define  I_DF 150 
#define  I_GET 149 
#define  I_HELP 148 
#define  I_LCHDIR 147 
#define  I_LINK 146 
#define  I_LLS 145 
#define  I_LMKDIR 144 
#define  I_LPWD 143 
#define  I_LS 142 
#define  I_LUMASK 141 
#define  I_MKDIR 140 
#define  I_PROGRESS 139 
#define  I_PUT 138 
#define  I_PWD 137 
#define  I_QUIT 136 
#define  I_REGET 135 
#define  I_RENAME 134 
#define  I_REPUT 133 
#define  I_RM 132 
#define  I_RMDIR 131 
#define  I_SHELL 130 
#define  I_SYMLINK 129 
#define  I_VERSION 128 
 int PATH_MAX ; 
 int SSH2_FILEXFER_ATTR_PERMISSIONS ; 
 int SSH2_FILEXFER_ATTR_UIDGID ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  attrib_clear (TYPE_2__*) ; 
 int chdir (char*) ; 
 int do_df (struct sftp_conn*,char*,int,int) ; 
 int do_globbed_ls (struct sftp_conn*,char*,char*,int) ; 
 int do_hardlink (struct sftp_conn*,char*,char*) ; 
 int /*<<< orphan*/  do_ls_dir (struct sftp_conn*,char*,char*,int) ; 
 int do_mkdir (struct sftp_conn*,char*,TYPE_2__*,int) ; 
 char* do_realpath (struct sftp_conn*,char*) ; 
 int do_rename (struct sftp_conn*,char*,char*,int) ; 
 int do_rm (struct sftp_conn*,char*) ; 
 int do_rmdir (struct sftp_conn*,char*) ; 
 int do_setstat (struct sftp_conn*,char*,TYPE_2__*) ; 
 TYPE_2__* do_stat (struct sftp_conn*,char*,int /*<<< orphan*/ ) ; 
 int do_symlink (struct sftp_conn*,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  interrupted ; 
 int /*<<< orphan*/  local_do_ls (char const*) ; 
 int /*<<< orphan*/  local_do_shell (char const*) ; 
 char* make_absolute (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  mprintf (char*,char*) ; 
 int parse_args (char const**,int*,int*,int*,int*,int*,int*,int*,int*,int*,unsigned long*,char**,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int process_get (struct sftp_conn*,char*,char*,char*,int,int,int,int) ; 
 int process_put (struct sftp_conn*,char*,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  remote_glob (struct sftp_conn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int sftp_proto_version (struct sftp_conn*) ; 
 int showprogress ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int stub1 (struct sftp_conn*,char*,char*) ; 
 char* tilde_expand_filename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (unsigned long) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int
parse_dispatch_command(struct sftp_conn *conn, const char *cmd, char **pwd,
    const char *startdir, int err_abort)
{
	char *path1, *path2, *tmp;
	int ignore_errors = 0, aflag = 0, fflag = 0, hflag = 0,
	iflag = 0;
	int lflag = 0, pflag = 0, rflag = 0, sflag = 0;
	int cmdnum, i;
	unsigned long n_arg = 0;
	Attrib a, *aa;
	char path_buf[PATH_MAX];
	int err = 0;
	glob_t g;

	path1 = path2 = NULL;
	cmdnum = parse_args(&cmd, &ignore_errors, &aflag, &fflag, &hflag,
	    &iflag, &lflag, &pflag, &rflag, &sflag, &n_arg, &path1, &path2);
	if (ignore_errors != 0)
		err_abort = 0;

	memset(&g, 0, sizeof(g));

	/* Perform command */
	switch (cmdnum) {
	case 0:
		/* Blank line */
		break;
	case -1:
		/* Unrecognized command */
		err = -1;
		break;
	case I_REGET:
		aflag = 1;
		/* FALLTHROUGH */
	case I_GET:
		err = process_get(conn, path1, path2, *pwd, pflag,
		    rflag, aflag, fflag);
		break;
	case I_REPUT:
		aflag = 1;
		/* FALLTHROUGH */
	case I_PUT:
		err = process_put(conn, path1, path2, *pwd, pflag,
		    rflag, aflag, fflag);
		break;
	case I_RENAME:
		path1 = make_absolute(path1, *pwd);
		path2 = make_absolute(path2, *pwd);
		err = do_rename(conn, path1, path2, lflag);
		break;
	case I_SYMLINK:
		sflag = 1;
	case I_LINK:
		if (!sflag)
			path1 = make_absolute(path1, *pwd);
		path2 = make_absolute(path2, *pwd);
		err = (sflag ? do_symlink : do_hardlink)(conn, path1, path2);
		break;
	case I_RM:
		path1 = make_absolute(path1, *pwd);
		remote_glob(conn, path1, GLOB_NOCHECK, NULL, &g);
		for (i = 0; g.gl_pathv[i] && !interrupted; i++) {
			if (!quiet)
				mprintf("Removing %s\n", g.gl_pathv[i]);
			err = do_rm(conn, g.gl_pathv[i]);
			if (err != 0 && err_abort)
				break;
		}
		break;
	case I_MKDIR:
		path1 = make_absolute(path1, *pwd);
		attrib_clear(&a);
		a.flags |= SSH2_FILEXFER_ATTR_PERMISSIONS;
		a.perm = 0777;
		err = do_mkdir(conn, path1, &a, 1);
		break;
	case I_RMDIR:
		path1 = make_absolute(path1, *pwd);
		err = do_rmdir(conn, path1);
		break;
	case I_CHDIR:
		if (path1 == NULL || *path1 == '\0')
			path1 = xstrdup(startdir);
		path1 = make_absolute(path1, *pwd);
		if ((tmp = do_realpath(conn, path1)) == NULL) {
			err = 1;
			break;
		}
		if ((aa = do_stat(conn, tmp, 0)) == NULL) {
			free(tmp);
			err = 1;
			break;
		}
		if (!(aa->flags & SSH2_FILEXFER_ATTR_PERMISSIONS)) {
			error("Can't change directory: Can't check target");
			free(tmp);
			err = 1;
			break;
		}
		if (!S_ISDIR(aa->perm)) {
			error("Can't change directory: \"%s\" is not "
			    "a directory", tmp);
			free(tmp);
			err = 1;
			break;
		}
		free(*pwd);
		*pwd = tmp;
		break;
	case I_LS:
		if (!path1) {
			do_ls_dir(conn, *pwd, *pwd, lflag);
			break;
		}

		/* Strip pwd off beginning of non-absolute paths */
		tmp = NULL;
		if (*path1 != '/')
			tmp = *pwd;

		path1 = make_absolute(path1, *pwd);
		err = do_globbed_ls(conn, path1, tmp, lflag);
		break;
	case I_DF:
		/* Default to current directory if no path specified */
		if (path1 == NULL)
			path1 = xstrdup(*pwd);
		path1 = make_absolute(path1, *pwd);
		err = do_df(conn, path1, hflag, iflag);
		break;
	case I_LCHDIR:
		if (path1 == NULL || *path1 == '\0')
			path1 = xstrdup("~");
		tmp = tilde_expand_filename(path1, getuid());
		free(path1);
		path1 = tmp;
		if (chdir(path1) == -1) {
			error("Couldn't change local directory to "
			    "\"%s\": %s", path1, strerror(errno));
			err = 1;
		}
		break;
	case I_LMKDIR:
		if (mkdir(path1, 0777) == -1) {
			error("Couldn't create local directory "
			    "\"%s\": %s", path1, strerror(errno));
			err = 1;
		}
		break;
	case I_LLS:
		local_do_ls(cmd);
		break;
	case I_SHELL:
		local_do_shell(cmd);
		break;
	case I_LUMASK:
		umask(n_arg);
		printf("Local umask: %03lo\n", n_arg);
		break;
	case I_CHMOD:
		path1 = make_absolute(path1, *pwd);
		attrib_clear(&a);
		a.flags |= SSH2_FILEXFER_ATTR_PERMISSIONS;
		a.perm = n_arg;
		remote_glob(conn, path1, GLOB_NOCHECK, NULL, &g);
		for (i = 0; g.gl_pathv[i] && !interrupted; i++) {
			if (!quiet)
				mprintf("Changing mode on %s\n",
				    g.gl_pathv[i]);
			err = do_setstat(conn, g.gl_pathv[i], &a);
			if (err != 0 && err_abort)
				break;
		}
		break;
	case I_CHOWN:
	case I_CHGRP:
		path1 = make_absolute(path1, *pwd);
		remote_glob(conn, path1, GLOB_NOCHECK, NULL, &g);
		for (i = 0; g.gl_pathv[i] && !interrupted; i++) {
			if (!(aa = do_stat(conn, g.gl_pathv[i], 0))) {
				if (err_abort) {
					err = -1;
					break;
				} else
					continue;
			}
			if (!(aa->flags & SSH2_FILEXFER_ATTR_UIDGID)) {
				error("Can't get current ownership of "
				    "remote file \"%s\"", g.gl_pathv[i]);
				if (err_abort) {
					err = -1;
					break;
				} else
					continue;
			}
			aa->flags &= SSH2_FILEXFER_ATTR_UIDGID;
			if (cmdnum == I_CHOWN) {
				if (!quiet)
					mprintf("Changing owner on %s\n",
					    g.gl_pathv[i]);
				aa->uid = n_arg;
			} else {
				if (!quiet)
					mprintf("Changing group on %s\n",
					    g.gl_pathv[i]);
				aa->gid = n_arg;
			}
			err = do_setstat(conn, g.gl_pathv[i], aa);
			if (err != 0 && err_abort)
				break;
		}
		break;
	case I_PWD:
		mprintf("Remote working directory: %s\n", *pwd);
		break;
	case I_LPWD:
		if (!getcwd(path_buf, sizeof(path_buf))) {
			error("Couldn't get local cwd: %s", strerror(errno));
			err = -1;
			break;
		}
		mprintf("Local working directory: %s\n", path_buf);
		break;
	case I_QUIT:
		/* Processed below */
		break;
	case I_HELP:
		help();
		break;
	case I_VERSION:
		printf("SFTP protocol version %u\n", sftp_proto_version(conn));
		break;
	case I_PROGRESS:
		showprogress = !showprogress;
		if (showprogress)
			printf("Progress meter enabled\n");
		else
			printf("Progress meter disabled\n");
		break;
	default:
		fatal("%d is not implemented", cmdnum);
	}

	if (g.gl_pathc)
		globfree(&g);
	free(path1);
	free(path2);

	/* If an unignored error occurs in batch mode we should abort. */
	if (err_abort && err != 0)
		return (-1);
	else if (cmdnum == I_QUIT)
		return (1);

	return (0);
}