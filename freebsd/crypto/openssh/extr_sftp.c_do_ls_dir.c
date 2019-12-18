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
typedef  int u_int ;
struct winsize {int ws_col; } ;
struct stat {int dummy; } ;
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  sb ;
struct TYPE_5__ {char* filename; int /*<<< orphan*/  longname; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ SFTP_DIRENT ;

/* Variables and functions */
 int LS_LONG_VIEW ; 
 int LS_NUMERIC_VIEW ; 
 int LS_REVERSE_SORT ; 
 int LS_SHORT_VIEW ; 
 int LS_SHOW_ALL ; 
 int LS_SI_UNITS ; 
 int MAXIMUM (int,int) ; 
 int MINIMUM (int,int) ; 
 int SORT_FLAGS ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  attrib_to_stat (int /*<<< orphan*/ *,struct stat*) ; 
 int do_readdir (struct sftp_conn*,char const*,TYPE_1__***) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_sftp_dirents (TYPE_1__**) ; 
 int /*<<< orphan*/  interrupted ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 char* ls_file (char*,struct stat*,int,int) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mprintf (char*,...) ; 
 char* path_append (char const*,char*) ; 
 char* path_strip (char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdirent_comp ; 
 int sort_flag ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static int
do_ls_dir(struct sftp_conn *conn, const char *path,
    const char *strip_path, int lflag)
{
	int n;
	u_int c = 1, colspace = 0, columns = 1;
	SFTP_DIRENT **d;

	if ((n = do_readdir(conn, path, &d)) != 0)
		return (n);

	if (!(lflag & LS_SHORT_VIEW)) {
		u_int m = 0, width = 80;
		struct winsize ws;
		char *tmp;

		/* Count entries for sort and find longest filename */
		for (n = 0; d[n] != NULL; n++) {
			if (d[n]->filename[0] != '.' || (lflag & LS_SHOW_ALL))
				m = MAXIMUM(m, strlen(d[n]->filename));
		}

		/* Add any subpath that also needs to be counted */
		tmp = path_strip(path, strip_path);
		m += strlen(tmp);
		free(tmp);

		if (ioctl(fileno(stdin), TIOCGWINSZ, &ws) != -1)
			width = ws.ws_col;

		columns = width / (m + 2);
		columns = MAXIMUM(columns, 1);
		colspace = width / columns;
		colspace = MINIMUM(colspace, width);
	}

	if (lflag & SORT_FLAGS) {
		for (n = 0; d[n] != NULL; n++)
			;	/* count entries */
		sort_flag = lflag & (SORT_FLAGS|LS_REVERSE_SORT);
		qsort(d, n, sizeof(*d), sdirent_comp);
	}

	for (n = 0; d[n] != NULL && !interrupted; n++) {
		char *tmp, *fname;

		if (d[n]->filename[0] == '.' && !(lflag & LS_SHOW_ALL))
			continue;

		tmp = path_append(path, d[n]->filename);
		fname = path_strip(tmp, strip_path);
		free(tmp);

		if (lflag & LS_LONG_VIEW) {
			if (lflag & (LS_NUMERIC_VIEW|LS_SI_UNITS)) {
				char *lname;
				struct stat sb;

				memset(&sb, 0, sizeof(sb));
				attrib_to_stat(&d[n]->a, &sb);
				lname = ls_file(fname, &sb, 1,
				    (lflag & LS_SI_UNITS));
				mprintf("%s\n", lname);
				free(lname);
			} else
				mprintf("%s\n", d[n]->longname);
		} else {
			mprintf("%-*s", colspace, fname);
			if (c >= columns) {
				printf("\n");
				c = 1;
			} else
				c++;
		}

		free(fname);
	}

	if (!(lflag & LS_LONG_VIEW) && (c != 1))
		printf("\n");

	free_sftp_dirents(d);
	return (0);
}