#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_ino; int /*<<< orphan*/  st_dev; } ;
struct directory {scalar_t__* di_name; TYPE_1__* di_prev; TYPE_1__* di_next; scalar_t__ di_count; } ;
struct TYPE_2__ {struct directory* di_prev; struct directory* di_next; } ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ DEV_DEV_COMPARE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* SAVE (char*) ; 
 int /*<<< orphan*/  STRNULL ; 
 int /*<<< orphan*/  STRdirstack ; 
 scalar_t__* Strsave (scalar_t__*) ; 
 int VAR_NOGLOB ; 
 int VAR_READWRITE ; 
 scalar_t__* agetcwd () ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  cleanup_ignore (scalar_t__*) ; 
 int /*<<< orphan*/  cleanup_push (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (scalar_t__*) ; 
 scalar_t__* dcanon (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ dhead ; 
 int /*<<< orphan*/  dnewcwd (struct directory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstart (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 scalar_t__ printd ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 char* short2str (scalar_t__*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct directory* xcalloc (int,int) ; 
 int /*<<< orphan*/  xexit (int) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dinit(Char *hp)
{
    Char *cp, *tcp;
    struct directory *dp;

    /* Don't believe the login shell home, because it may be a symlink */
    tcp = agetcwd();
    if (tcp == NULL) {
	xprintf("%s: %s\n", progname, strerror(errno));
	if (hp && *hp) {
	    char *xcp = short2str(hp);
	    dstart(xcp);
	    if (chdir(xcp) == -1)
		cp = NULL;
	    else
		cp = Strsave(hp);
	}
	else
	    cp = NULL;
	if (cp == NULL) {
	    dstart("/");
	    if (chdir("/") == -1)
		/* I am not even try to print an error message! */
		xexit(1);
	    cp = SAVE("/");
	}
    }
    else {
#ifdef S_IFLNK
	struct stat swd, shp;
	int swd_ok;

	swd_ok = stat(short2str(tcp), &swd) == 0;
	/*
	 * See if $HOME is the working directory we got and use that
	 */
	if (swd_ok && hp && *hp && stat(short2str(hp), &shp) != -1 &&
	    DEV_DEV_COMPARE(swd.st_dev, shp.st_dev)  &&
		swd.st_ino == shp.st_ino)
	    cp = Strsave(hp);
	else {
	    char   *cwd;

	    /*
	     * use PWD if we have it (for subshells)
	     */
	    if (swd_ok && (cwd = getenv("PWD")) != NULL) {
		if (stat(cwd, &shp) != -1 &&
			DEV_DEV_COMPARE(swd.st_dev, shp.st_dev) &&
		        swd.st_ino == shp.st_ino) {
		    tcp = SAVE(cwd);
		    cleanup_push(tcp, xfree);
		}
	    }
	    cleanup_push(tcp, xfree);
	    cp = dcanon(tcp, STRNULL);
	    cleanup_ignore(tcp);
	    cleanup_until(tcp);
	}
#else /* S_IFLNK */
	cleanup_push(tcp, xfree);
	cp = dcanon(tcp, STRNULL);
	cleanup_ignore(tcp);
	cleanup_until(tcp);
#endif /* S_IFLNK */
    }

    dp = xcalloc(sizeof(struct directory), 1);
    dp->di_name = cp;
    dp->di_count = 0;
    dhead.di_next = dhead.di_prev = dp;
    dp->di_next = dp->di_prev = &dhead;
    printd = 0;
    dnewcwd(dp, 0);
    setcopy(STRdirstack, dp->di_name, VAR_READWRITE|VAR_NOGLOB);
}