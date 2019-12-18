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
typedef  size_t u_int ;
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  ins ;
struct TYPE_8__ {int gl_matchc; int /*<<< orphan*/  gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  g ;
struct TYPE_9__ {char* cursor; } ;
typedef  TYPE_2__ LineInfo ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int GLOB_DOOFFS ; 
 int GLOB_MARK ; 
 int LOCAL ; 
 char* complete_ambiguous (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete_display (int /*<<< orphan*/ ,size_t) ; 
 int el_insertstr (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* el_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 char* make_absolute (char*,char*) ; 
 int mblen (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* path_strip (char*,char*) ; 
 int /*<<< orphan*/  remote_glob (struct sftp_conn*,char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
complete_match(EditLine *el, struct sftp_conn *conn, char *remote_path,
    char *file, int remote, int lastarg, char quote, int terminated)
{
	glob_t g;
	char *tmp, *tmp2, ins[8];
	u_int i, hadglob, pwdlen, len, tmplen, filelen, cesc, isesc, isabs;
	int clen;
	const LineInfo *lf;

	/* Glob from "file" location */
	if (file == NULL)
		tmp = xstrdup("*");
	else
		xasprintf(&tmp, "%s*", file);

	/* Check if the path is absolute. */
	isabs = tmp[0] == '/';

	memset(&g, 0, sizeof(g));
	if (remote != LOCAL) {
		tmp = make_absolute(tmp, remote_path);
		remote_glob(conn, tmp, GLOB_DOOFFS|GLOB_MARK, NULL, &g);
	} else
		glob(tmp, GLOB_DOOFFS|GLOB_MARK, NULL, &g);

	/* Determine length of pwd so we can trim completion display */
	for (hadglob = tmplen = pwdlen = 0; tmp[tmplen] != 0; tmplen++) {
		/* Terminate counting on first unescaped glob metacharacter */
		if (tmp[tmplen] == '*' || tmp[tmplen] == '?') {
			if (tmp[tmplen] != '*' || tmp[tmplen + 1] != '\0')
				hadglob = 1;
			break;
		}
		if (tmp[tmplen] == '\\' && tmp[tmplen + 1] != '\0')
			tmplen++;
		if (tmp[tmplen] == '/')
			pwdlen = tmplen + 1;	/* track last seen '/' */
	}
	free(tmp);
	tmp = NULL;

	if (g.gl_matchc == 0)
		goto out;

	if (g.gl_matchc > 1)
		complete_display(g.gl_pathv, pwdlen);

	/* Don't try to extend globs */
	if (file == NULL || hadglob)
		goto out;

	tmp2 = complete_ambiguous(file, g.gl_pathv, g.gl_matchc);
	tmp = path_strip(tmp2, isabs ? NULL : remote_path);
	free(tmp2);

	if (tmp == NULL)
		goto out;

	tmplen = strlen(tmp);
	filelen = strlen(file);

	/* Count the number of escaped characters in the input string. */
	cesc = isesc = 0;
	for (i = 0; i < filelen; i++) {
		if (!isesc && file[i] == '\\' && i + 1 < filelen){
			isesc = 1;
			cesc++;
		} else
			isesc = 0;
	}

	if (tmplen > (filelen - cesc)) {
		tmp2 = tmp + filelen - cesc;
		len = strlen(tmp2);
		/* quote argument on way out */
		for (i = 0; i < len; i += clen) {
			if ((clen = mblen(tmp2 + i, len - i)) < 0 ||
			    (size_t)clen > sizeof(ins) - 2)
				fatal("invalid multibyte character");
			ins[0] = '\\';
			memcpy(ins + 1, tmp2 + i, clen);
			ins[clen + 1] = '\0';
			switch (tmp2[i]) {
			case '\'':
			case '"':
			case '\\':
			case '\t':
			case '[':
			case ' ':
			case '#':
			case '*':
				if (quote == '\0' || tmp2[i] == quote) {
					if (el_insertstr(el, ins) == -1)
						fatal("el_insertstr "
						    "failed.");
					break;
				}
				/* FALLTHROUGH */
			default:
				if (el_insertstr(el, ins + 1) == -1)
					fatal("el_insertstr failed.");
				break;
			}
		}
	}

	lf = el_line(el);
	if (g.gl_matchc == 1) {
		i = 0;
		if (!terminated && quote != '\0')
			ins[i++] = quote;
		if (*(lf->cursor - 1) != '/' &&
		    (lastarg || *(lf->cursor) != ' '))
			ins[i++] = ' ';
		ins[i] = '\0';
		if (i > 0 && el_insertstr(el, ins) == -1)
			fatal("el_insertstr failed.");
	}
	free(tmp);

 out:
	globfree(&g);
	return g.gl_matchc;
}