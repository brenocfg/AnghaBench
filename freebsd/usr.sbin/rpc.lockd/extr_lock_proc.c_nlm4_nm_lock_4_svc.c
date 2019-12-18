#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat; } ;
struct TYPE_7__ {TYPE_1__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nlm4_res ;
struct TYPE_8__ {int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm4_lockargs ;

/* Variables and functions */
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  nlm4_granted ; 

nlm4_res *
nlm4_nm_lock_4_svc(nlm4_lockargs *arg, struct svc_req *rqstp)
{
	static nlm4_res res;

	if (debug_level)
		log_from_addr("nlm4_nm_lock", rqstp);

	/* copy cookie from arg to result.  See comment in nlm4_test_1() */
	res.cookie = arg->cookie;
	res.stat.stat = nlm4_granted;
	return (&res);
}