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
struct stat {int st_mode; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  STRlistlinks ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCDF (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISHIDDEN (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISNWK (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 char* Strspl (char*,char*) ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int lstat (char*,struct stat*) ; 
 scalar_t__ nostat (char*) ; 
 char* short2str (char*) ; 
 int stat (char*,struct stat*) ; 
 char* strspl (char*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static  Char
filetype(Char *dir, Char *file)
{
    if (dir) {
	Char *path;
	char   *ptr;
	struct stat statb;

	if (nostat(dir)) return(' ');

	path = Strspl(dir, file);
	ptr = short2str(path);
	xfree(path);

	if (lstat(ptr, &statb) != -1) {
#ifdef S_ISLNK
	    if (S_ISLNK(statb.st_mode)) {	/* Symbolic link */
		if (adrof(STRlistlinks)) {
		    if (stat(ptr, &statb) == -1)
			return ('&');
		    else if (S_ISDIR(statb.st_mode))
			return ('>');
		    else
			return ('@');
		}
		else
		    return ('@');
	    }
#endif
#ifdef S_ISSOCK
	    if (S_ISSOCK(statb.st_mode))	/* Socket */
		return ('=');
#endif
#ifdef S_ISFIFO
	    if (S_ISFIFO(statb.st_mode)) /* Named Pipe */
		return ('|');
#endif
#ifdef S_ISHIDDEN
	    if (S_ISHIDDEN(statb.st_mode)) /* Hidden Directory [aix] */
		return ('+');
#endif
#ifdef S_ISCDF
	    {
		struct stat hpstatb;
		char *p2;

		p2 = strspl(ptr, "+");	/* Must append a '+' and re-stat(). */
		if ((stat(p2, &hpstatb) != -1) && S_ISCDF(hpstatb.st_mode)) {
		    xfree(p2);
		    return ('+');	/* Context Dependent Files [hpux] */
		}
		xfree(p2);
	    }
#endif
#ifdef S_ISNWK
	    if (S_ISNWK(statb.st_mode)) /* Network Special [hpux] */
		return (':');
#endif
#ifdef S_ISCHR
	    if (S_ISCHR(statb.st_mode))	/* char device */
		return ('%');
#endif
#ifdef S_ISBLK
	    if (S_ISBLK(statb.st_mode))	/* block device */
		return ('#');
#endif
#ifdef S_ISDIR
	    if (S_ISDIR(statb.st_mode))	/* normal Directory */
		return ('/');
#endif
	    if (statb.st_mode & (S_IXUSR|S_IXGRP|S_IXOTH))
		return ('*');
	}
    }
    return (' ');
}