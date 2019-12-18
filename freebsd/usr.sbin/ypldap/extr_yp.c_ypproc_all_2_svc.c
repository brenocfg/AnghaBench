#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ypresp_all {int dummy; } ;
typedef  struct ypresp_all ypresp_all ;
struct TYPE_3__ {int /*<<< orphan*/  domain; } ;
typedef  TYPE_1__ ypreq_nokey ;
struct ypresp_val {int dummy; } ;
struct svc_req {int /*<<< orphan*/  rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_FAILED ; 
 int /*<<< orphan*/  svcerr_auth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yp_valid_domain (int /*<<< orphan*/ ,struct ypresp_val*) ; 

ypresp_all *
ypproc_all_2_svc(ypreq_nokey *arg, struct svc_req *req)
{
	static struct ypresp_all	res;

	if (yp_valid_domain(arg->domain, (struct ypresp_val *)&res) == -1)
		return (&res);

	svcerr_auth(req->rq_xprt, AUTH_FAILED);
	return (NULL);
}