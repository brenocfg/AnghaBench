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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int FSHTTY ; 
 int NOFILE ; 
 int OLDSTD ; 
 int O_LARGEFILE ; 
 int O_RDONLY ; 
 int SHDIAG ; 
 int SHIN ; 
 int SHOUT ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  fix_yp_bugs () ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 
 int /*<<< orphan*/  xclose (int) ; 
 int /*<<< orphan*/  xopen (int /*<<< orphan*/ ,int) ; 

void
closem(void)
{
    int f, num_files;
#ifdef S_ISSOCK
    struct stat st;
#endif /*S_ISSOCK*/

#ifdef NLS_BUGS
#ifdef NLS_CATALOGS
    nlsclose();
#endif /* NLS_CATALOGS */
#endif /* NLS_BUGS */
#ifdef YPBUGS
    /* suggested by Justin Bur; thanks to Karl Kleinpaste */
    fix_yp_bugs();
#endif /* YPBUGS */
    num_files = NOFILE;
    for (f = 0; f < num_files; f++)
	if (f != SHIN && f != SHOUT && f != SHDIAG && f != OLDSTD &&
	    f != FSHTTY 
#ifdef MALLOC_TRACE
	    && f != 25
#endif /* MALLOC_TRACE */
#ifdef S_ISSOCK
	    /* NSS modules (e.g. Linux nss_ldap) might keep sockets open.
	     * If we close such a socket, both the NSS module and tcsh think
	     * they "own" the descriptor.
	     *
	     * Not closing sockets does not make the cleanup use of closem()
	     * less reliable because tcsh never creates sockets.
	     */
	    && fstat(f, &st) == 0 && !S_ISSOCK(st.st_mode)	
#endif
	    )
	  {
	    xclose(f);
#ifdef NISPLUS
	    if(f < 3)
		(void) xopen(_PATH_DEVNULL, O_RDONLY|O_LARGEFILE);
#endif /* NISPLUS */
	  }
#ifdef NLS_BUGS
#ifdef NLS_CATALOGS
    nlsinit();
#endif /* NLS_CATALOGS */
#endif /* NLS_BUGS */
}