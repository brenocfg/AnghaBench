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
typedef  scalar_t__ u_short ;
struct varlist {int dummy; } ;
typedef  int associd_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READVAR ; 
 char* currenthost ; 
 int doprintpeers (struct varlist*,int,int,size_t,char const*,int /*<<< orphan*/ *,int) ; 
 int doquery (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,size_t*,char const**) ; 
 int doquerylist (struct varlist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,size_t*,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int numhosts ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
dogetpeers(
	struct varlist *pvl,
	associd_t associd,
	FILE *fp,
	int af
	)
{
	const char *datap;
	int res;
	size_t dsize;
	u_short rstatus;

#ifdef notdef
	res = doquerylist(pvl, CTL_OP_READVAR, associd, 0, &rstatus,
			  &dsize, &datap);
#else
	/*
	 * Damn fuzzballs
	 */
	res = doquery(CTL_OP_READVAR, associd, 0, 0, NULL, &rstatus,
			  &dsize, &datap);
#endif

	if (res != 0)
		return 0;

	if (dsize == 0) {
		if (numhosts > 1)
			fprintf(stderr, "server=%s ", currenthost);
		fprintf(stderr,
			"***No information returned for association %u\n",
			associd);
		return 0;
	}

	return doprintpeers(pvl, associd, (int)rstatus, dsize, datap,
			    fp, af);
}