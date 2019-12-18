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
struct svc_req {int dummy; } ;

/* Variables and functions */
 scalar_t__ yp_access (int /*<<< orphan*/ *,struct svc_req*,...) ; 

void *
ypproc_null_2_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;
	static char rval = 0;

#ifdef DB_CACHE
	if (yp_access(NULL, NULL, (struct svc_req *)rqstp))
#else
	if (yp_access(NULL, (struct svc_req *)rqstp))
#endif
		return(NULL);

	result = &rval;

	return((void *) &result);
}