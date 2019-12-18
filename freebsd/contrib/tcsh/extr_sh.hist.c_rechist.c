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
struct varent {scalar_t__* vec; } ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  jmp_buf_t ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  G_ERROR ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ReplaceFile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SHOUT ; 
 char* STRNULL ; 
 char* const STRhistfile ; 
#define  STRhistory 129 
 char* const STRhome ; 
 int /*<<< orphan*/  STRlock ; 
 char* STRmaxint ; 
 int /*<<< orphan*/  STRmerge ; 
#define  STRmhT 128 
 char* const STRsavehist ; 
 int /*<<< orphan*/ * STRtildothist ; 
 char* Strsave (char*) ; 
 char* Strspl (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCSH_IGNORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (struct stat) ; 
 struct varent* adrof (char* const) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int didfds ; 
 int /*<<< orphan*/  dohist (char**,int /*<<< orphan*/ *) ; 
 scalar_t__ dot_lock (char*,int) ; 
 int /*<<< orphan*/  dotlock_cleanup (char*) ; 
 scalar_t__ eq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchmod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getexit (int /*<<< orphan*/ ) ; 
 char* globone (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadhist (char*,int) ; 
 char* randsuf () ; 
 int /*<<< orphan*/  rename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resexit (int /*<<< orphan*/ ) ; 
 scalar_t__ setexit () ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 
 char* strsave (int /*<<< orphan*/ ) ; 
 char* varval (char* const) ; 
 int /*<<< orphan*/  xclose (int) ; 
 int xcreat (char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*) ; 

void
rechist(Char *fname, int ref)
{
    Char    *snum, *rs;
    int     fp, ftmp, oldidfds;
    struct varent *shist;
    char path[MAXPATHLEN];
    struct stat st;
    static Char   *dumphist[] = {STRhistory, STRmhT, 0, 0};

    if (fname == NULL && !ref) 
	return;
    /*
     * If $savehist is just set, we use the value of $history
     * else we use the value in $savehist
     */
    if (((snum = varval(STRsavehist)) == STRNULL) &&
	((snum = varval(STRhistory)) == STRNULL))
	snum = STRmaxint;


    if (fname == NULL) {
	if ((fname = varval(STRhistfile)) == STRNULL)
	    fname = Strspl(varval(STRhome), &STRtildothist[1]);
	else
	    fname = Strsave(fname);
    }
    else
	fname = globone(fname, G_ERROR);
    cleanup_push(fname, xfree);

    /*
     * The 'savehist merge' feature is intended for an environment
     * with numerous shells being in simultaneous use. Imagine
     * any kind of window system. All these shells 'share' the same 
     * ~/.history file for recording their command line history. 
     * We try to handle the case of multiple shells trying to merge
     * histories at the same time, by creating semi-unique filenames
     * and saving the history there first and then trying to rename
     * them in the proper history file.
     *
     * Users that like to nuke their environment require here an atomic
     * loadhist-creat-dohist(dumphist)-close sequence which is given
		 * by optional lock parameter to savehist.
     *
     * jw.
     */ 
    /*
     * We need the didfds stuff before loadhist otherwise
     * exec in a script will fail to print if merge is set.
     * From: mveksler@iil.intel.com (Veksler Michael)
     */
    oldidfds = didfds;
    didfds = 0;
    if ((shist = adrof(STRsavehist)) != NULL && shist->vec != NULL) {
	size_t i;
	int merge = 0, lock = 0;

	for (i = 1; shist->vec[i]; i++) {
	    if (eq(shist->vec[i], STRmerge))
		merge++;
	    if (eq(shist->vec[i], STRlock))
		lock++;
	}

	if (merge) {
	    jmp_buf_t osetexit;
	    if (lock) {
#ifndef WINNT_NATIVE
		char *lockpath = strsave(short2str(fname));
		cleanup_push(lockpath, xfree);
		/* Poll in 100 miliseconds interval to obtain the lock. */
		if ((dot_lock(lockpath, 100) == 0))
		    cleanup_push(lockpath, dotlock_cleanup);
#endif
	    }
	    getexit(osetexit);
	    if (setexit())
		loadhist(fname, 1);
	    resexit(osetexit);
	}
    }
    rs = randsuf();
    xsnprintf(path, sizeof(path), "%S.%S", fname, rs);
    xfree(rs);

    fp = xcreat(path, 0600);
    if (fp == -1) {
	didfds = oldidfds;
	cleanup_until(fname);
	return;
    }
    /* Try to preserve ownership and permissions of the original history file */
#ifndef WINNT_NATIVE
    if (stat(short2str(fname), &st) != -1) {
	TCSH_IGNORE(fchown(fp, st.st_uid, st.st_gid));
	TCSH_IGNORE(fchmod(fp, st.st_mode));
    }
#else
    UNREFERENCED_PARAMETER(st);
#endif
    ftmp = SHOUT;
    SHOUT = fp;
    dumphist[2] = snum;
    dohist(dumphist, NULL);
    xclose(fp);
    SHOUT = ftmp;
    didfds = oldidfds;
#ifndef WINNT_NATIVE
    (void)rename(path, short2str(fname));
#else
    (void)ReplaceFile( short2str(fname),path,NULL,0,NULL,NULL);
#endif
    cleanup_until(fname);
}