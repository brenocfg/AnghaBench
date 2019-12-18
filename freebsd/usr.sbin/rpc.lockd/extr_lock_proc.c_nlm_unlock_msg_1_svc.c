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
struct nlm4_lock {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  alock; } ;
typedef  TYPE_2__ nlm_unlockargs ;
struct TYPE_6__ {int /*<<< orphan*/  stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  cookie; TYPE_1__ stat; } ;
typedef  TYPE_3__ nlm_res ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_UNLOCK_RES ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  getrpcaddr (struct svc_req*) ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  nlmtonlm4 (int /*<<< orphan*/ *,struct nlm4_lock*) ; 
 int /*<<< orphan*/  transmit_result (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (struct nlm4_lock*,int /*<<< orphan*/ ) ; 

void *
nlm_unlock_msg_1_svc(nlm_unlockargs *arg, struct svc_req *rqstp)
{
	static nlm_res res;
	struct nlm4_lock arg4;

	nlmtonlm4(&arg->alock, &arg4);

	if (debug_level)
		log_from_addr("nlm_unlock_msg", rqstp);

	res.stat.stat = unlock(&arg4, 0);
	res.cookie = arg->cookie;

	transmit_result(NLM_UNLOCK_RES, &res, getrpcaddr(rqstp));
	return (NULL);
}