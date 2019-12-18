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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
struct login_time {int dummy; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct login_time*) ; 
 int in_ltms (struct login_time*,struct tm*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (scalar_t__*) ; 
 struct login_time* login_timelist (int /*<<< orphan*/ *,char*,int*,struct login_time**) ; 

int
auth_timeok(login_cap_t *lc, time_t t)
{
    int	    rc = 1; /* Default is ok */

    if (lc != NULL && t != (time_t)0 && t != (time_t)-1) {
	struct tm	*tptr;

	static int 	ltimesno = 0;
	static struct login_time *ltimes = NULL;

	if ((tptr = localtime(&t)) != NULL) {
	    struct login_time	*lt;

	  lt = login_timelist(lc, "times.allow", &ltimesno, &ltimes);
	  if (lt != NULL && in_ltms(lt, tptr, NULL) == -1)
	      rc = 0;	  /* not in allowed times list */
	  else {

	      lt = login_timelist(lc, "times.deny", &ltimesno, &ltimes);
	      if (lt != NULL && in_ltms(lt, tptr, NULL) != -1)
		  rc = 0; /* in deny times list */
	  }
	  if (ltimes) {
	      free(ltimes);
	      ltimes = NULL;
	      ltimesno = 0;
	  }
	}
    }

    return rc;
}