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
struct varent {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_NOMATCH ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VAR_FIRST ; 
 int VAR_LAST ; 
 int VAR_NOGLOB ; 
 int /*<<< orphan*/  blkfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** globall (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  setq (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,struct varent*,int) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int tglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
set1(const Char *var, Char **vec, struct varent *head, int flags)
{
    Char **oldv = vec;

    if ((flags & VAR_NOGLOB) == 0) {
	int gflag;

	gflag = tglob(oldv);
	if (gflag) {
	    vec = globall(oldv, gflag);
	    if (vec == 0) {
		blkfree(oldv);
		stderror(ERR_NAME | ERR_NOMATCH);
	    }
	    blkfree(oldv);
	}
    }
    /*
     * Uniqueness addition from: Michael Veksler <mveksler@vnet.ibm.com>
     */
    if ( flags & (VAR_FIRST | VAR_LAST) ) {
	/*
	 * Code for -f (VAR_FIRST) and -l (VAR_LAST) options.
	 * Method:
	 *  Delete all duplicate words leaving "holes" in the word array (vec).
	 *  Then remove the "holes", keeping the order of the words unchanged.
	 */
	if (vec && vec[0] && vec[1]) { /* more than one word ? */
	    int i, j;
	    int num_items;

	    for (num_items = 0; vec[num_items]; num_items++)
	        continue;
	    if (flags & VAR_FIRST) {
		/* delete duplications, keeping first occurance */
		for (i = 1; i < num_items; i++)
		    for (j = 0; j < i; j++)
			/* If have earlier identical item, remove i'th item */
			if (vec[i] && vec[j] && Strcmp(vec[j], vec[i]) == 0) {
			    xfree(vec[i]);
			    vec[i] = NULL;
			    break;
			}
	    } else if (flags & VAR_LAST) {
	      /* delete duplications, keeping last occurance */
		for (i = 0; i < num_items - 1; i++)
		    for (j = i + 1; j < num_items; j++)
			/* If have later identical item, remove i'th item */
			if (vec[i] && vec[j] && Strcmp(vec[j], vec[i]) == 0) {
			    /* remove identical item (the first) */
			    xfree(vec[i]);
			    vec[i] = NULL;
			}
	    }
	    /* Compress items - remove empty items */
	    for (j = i = 0; i < num_items; i++)
	       if (vec[i]) 
		  vec[j++] = vec[i];

	    /* NULL-fy remaining items */
	    for (; j < num_items; j++)
		 vec[j] = NULL;
	}
	/* don't let the attribute propagate */
	flags &= ~(VAR_FIRST|VAR_LAST);
    } 
    setq(var, vec, head, flags);
}