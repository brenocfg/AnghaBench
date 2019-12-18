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
struct netpath_vars {scalar_t__ valid; int /*<<< orphan*/  ncp; struct netpath_vars* nchain_next; struct netpath_vars* ncp_list; struct netpath_vars* netpath_start; int /*<<< orphan*/ * nc_handlep; } ;
struct netpath_chain {scalar_t__ valid; int /*<<< orphan*/  ncp; struct netpath_chain* nchain_next; struct netpath_chain* ncp_list; struct netpath_chain* netpath_start; int /*<<< orphan*/ * nc_handlep; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ NP_VALID ; 
 int /*<<< orphan*/  endnetconfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct netpath_vars*) ; 
 int /*<<< orphan*/  freenetconfigent (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc_verify () ; 
 int /*<<< orphan*/  stderr ; 

int
endnetpath(void *handlep)
{
    struct netpath_vars *np_sessionp = (struct netpath_vars *)handlep;
    struct netpath_chain *chainp, *lastp;

    if (np_sessionp == NULL || np_sessionp->valid != NP_VALID) {
	errno = EINVAL;
	return (-1);
    }
    if (np_sessionp->nc_handlep != NULL)
	endnetconfig(np_sessionp->nc_handlep);
    if (np_sessionp->netpath_start != NULL)
	free(np_sessionp->netpath_start);
    for (chainp = np_sessionp->ncp_list; chainp != NULL;
	    lastp=chainp, chainp=chainp->nchain_next, free(lastp)) {
	freenetconfigent(chainp->ncp);
    }
    free(np_sessionp);
#ifdef MEM_CHK
    if (malloc_verify() == 0) {
	fprintf(stderr, "memory heap corrupted in endnetpath\n");
	exit(1);
    }
#endif
    return (0);
}