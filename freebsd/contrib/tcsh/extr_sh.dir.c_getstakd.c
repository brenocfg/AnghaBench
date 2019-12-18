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
struct directory {int /*<<< orphan*/  const* di_name; struct directory* di_prev; struct directory* di_next; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 struct directory* dcwd ; 
 struct directory dhead ; 

const Char *
getstakd(int cnt)
{
    struct directory *dp;

    dp = dcwd;
    if (cnt < 0) {		/* < 0 ==> last dir requested. */
	dp = dp->di_next;
	if (dp == &dhead)
	    dp = dp->di_next;
    }
    else {
	while (cnt-- > 0) {
	    dp = dp->di_prev;
	    if (dp == &dhead)
		dp = dp->di_prev;
	    if (dp == dcwd)
		return NULL;
	}
    }
    return dp->di_name;
}