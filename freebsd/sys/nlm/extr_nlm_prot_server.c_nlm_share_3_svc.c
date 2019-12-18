#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm_shareres ;
struct TYPE_10__ {int /*<<< orphan*/  reclaim; int /*<<< orphan*/  share; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nlm_shareargs ;
struct TYPE_11__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm4_shareres ;
struct TYPE_12__ {int /*<<< orphan*/  reclaim; int /*<<< orphan*/  share; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_4__ nlm4_shareargs ;
typedef  scalar_t__ bool_t ;

/* Variables and functions */
 scalar_t__ nlm4_share_4_svc (TYPE_4__*,TYPE_3__*,struct svc_req*) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_share (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_stats (int /*<<< orphan*/ ) ; 

bool_t
nlm_share_3_svc(nlm_shareargs *argp, nlm_shareres *result, struct svc_req *rqstp)
{
	bool_t retval;
	nlm4_shareargs args4;
	nlm4_shareres res4;

	args4.cookie = argp->cookie;
	nlm_convert_to_nlm4_share(&args4.share, &argp->share);
	args4.reclaim = argp->reclaim;

	retval = nlm4_share_4_svc(&args4, &res4, rqstp);
	if (retval) {
		result->cookie = res4.cookie;
		result->stat = nlm_convert_to_nlm_stats(res4.stat);
		result->sequence = res4.sequence;
	}

	return (retval);
}