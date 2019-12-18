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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READVAR ; 
 char* currenthost ; 
 int doquery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int numhosts ; 
 int /*<<< orphan*/  stderr ; 

size_t
ntpq_read_sysvars(
	char *	resultbuf,
	size_t	maxsize
	)
{
	const char *	datap;
	int		res;
	size_t		dsize;
	u_short		rstatus;

	res = doquery(CTL_OP_READVAR, 0, 0, 0, NULL, &rstatus,
		      &dsize, &datap);

	if (res != 0)
		return 0;

	if (dsize == 0) {
		if (numhosts > 1)
			fprintf(stderr, "server=%s ", currenthost);
		fprintf(stderr, "***No sysvar information returned\n");

		return 0;
	} else {
		dsize = min(dsize, maxsize);
		memcpy(resultbuf, datap, dsize);
	}

	return dsize;
}