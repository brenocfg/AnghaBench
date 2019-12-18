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
typedef  int /*<<< orphan*/  sub ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,char const*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void build_workdir_tree(const char *root, int dirs, int subs)
{
	int i, j;
	char buf[64], sub[80];

	for (i = 0; i < dirs; ++i) {
		if (i % 2 == 0) {
			p_snprintf(buf, sizeof(buf), "%s/dir%02d", root, i);
			cl_git_pass(git_futils_mkdir(buf, 0775, GIT_MKDIR_PATH));

			p_snprintf(buf, sizeof(buf), "%s/dir%02d/file", root, i);
			cl_git_mkfile(buf, buf);
			buf[strlen(buf) - 5] = '\0';
		} else {
			p_snprintf(buf, sizeof(buf), "%s/DIR%02d", root, i);
			cl_git_pass(git_futils_mkdir(buf, 0775, GIT_MKDIR_PATH));
		}

		for (j = 0; j < subs; ++j) {
			switch (j % 4) {
			case 0: p_snprintf(sub, sizeof(sub), "%s/sub%02d", buf, j); break;
			case 1: p_snprintf(sub, sizeof(sub), "%s/sUB%02d", buf, j); break;
			case 2: p_snprintf(sub, sizeof(sub), "%s/Sub%02d", buf, j); break;
			case 3: p_snprintf(sub, sizeof(sub), "%s/SUB%02d", buf, j); break;
			}
			cl_git_pass(git_futils_mkdir(sub, 0775, GIT_MKDIR_PATH));

			if (j % 2 == 0) {
				size_t sublen = strlen(sub);
				memcpy(&sub[sublen], "/file", sizeof("/file"));
				cl_git_mkfile(sub, sub);
				sub[sublen] = '\0';
			}
		}
	}
}