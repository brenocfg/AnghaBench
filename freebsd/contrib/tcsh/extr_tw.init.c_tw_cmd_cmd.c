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
struct varent {char** vec; } ;
struct dirent {char* d_name; scalar_t__ d_ino; } ;
typedef  char DIR ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  STRpath ; 
 int /*<<< orphan*/  STRrecognize_only_executables ; 
 int /*<<< orphan*/  STRslash ; 
 size_t Strlen (char*) ; 
 char* Strspl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_FL_REL ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  executable (char*,char*,int /*<<< orphan*/ ) ; 
 char* opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendir_cleanup ; 
 struct dirent* readdir (char*) ; 
 int /*<<< orphan*/  short2str (char*) ; 
 char* str2short (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tw_cmd_add (char*) ; 
 int /*<<< orphan*/  tw_cmd_got ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
tw_cmd_cmd(void)
{
    DIR *dirp;
    struct dirent *dp;
    Char *dir = NULL, *name;
    Char **pv;
    struct varent *v = adrof(STRpath);
    struct varent *recexec = adrof(STRrecognize_only_executables);
    size_t len;


    if (v == NULL || v->vec == NULL) /* if no path */
	return;

    for (pv = v->vec; *pv; pv++) {
	if (pv[0][0] != '/') {
	    tw_cmd_got |= TW_FL_REL;
	    continue;
	}

	if ((dirp = opendir(short2str(*pv))) == NULL)
	    continue;

	cleanup_push(dirp, opendir_cleanup);
	if (recexec) {
	    dir = Strspl(*pv, STRslash);
	    cleanup_push(dir, xfree);
	}
	while ((dp = readdir(dirp)) != NULL) {
#if defined(_UWIN) || defined(__CYGWIN__)
	    /* Turn foo.{exe,com,bat} into foo since UWIN's readdir returns
	     * the file with the .exe, .com, .bat extension
	     *
	     * Same for Cygwin, but only for .exe and .com extension.
	     */
	    len = strlen(dp->d_name);
	    if (len > 4 && (strcmp(&dp->d_name[len - 4], ".exe") == 0 ||
#ifndef __CYGWIN__
		strcmp(&dp->d_name[len - 4], ".bat") == 0 ||
#endif /* !__CYGWIN__ */
		strcmp(&dp->d_name[len - 4], ".com") == 0))
		dp->d_name[len - 4] = '\0';
#endif /* _UWIN || __CYGWIN__ */
	    /* the call to executable() may make this a bit slow */
	    name = str2short(dp->d_name);
	    if (dp->d_ino == 0 || (recexec && !executable(dir, name, 0)))
		continue;
            len = Strlen(name);
            if (name[0] == '#' ||	/* emacs temp files	*/
		name[0] == '.' ||	/* .files		*/
		name[len - 1] == '~' ||	/* emacs backups	*/
		name[len - 1] == '%')	/* textedit backups	*/
                continue;		/* Ignore!		*/
            tw_cmd_add(name);
	}
	cleanup_until(dirp);
    }
}