#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_5__ {int sequence; int /*<<< orphan*/  stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm4_shareres ;
struct TYPE_6__ {int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nlm4_shareargs ;

/* Variables and functions */
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  nlm4_granted ; 

nlm4_shareres *
nlm4_share_4_svc(nlm4_shareargs *arg, struct svc_req *rqstp)
{
	static nlm4_shareres res;

	if (debug_level)
		log_from_addr("nlm4_share", rqstp);

	res.cookie = arg->cookie;
	res.stat = nlm4_granted;
	res.sequence = 1234356;	/* X/Open says this field is ignored? */
	return (&res);
}