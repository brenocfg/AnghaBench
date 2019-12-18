#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  svid; } ;
struct TYPE_9__ {int /*<<< orphan*/  cookie; TYPE_2__ alock; } ;
typedef  TYPE_3__ nlm4_testargs ;
struct TYPE_7__ {int /*<<< orphan*/  stat; } ;
struct TYPE_10__ {TYPE_1__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_4__ nlm4_res ;

/* Variables and functions */
 int /*<<< orphan*/  NLM4_GRANTED_RES ; 
 int /*<<< orphan*/  NLM_VERS4 ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  getrpcaddr (struct svc_req*) ; 
 scalar_t__ lock_answer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  nlm4_denied ; 
 int /*<<< orphan*/  nlm4_granted ; 
 int /*<<< orphan*/  transmit4_result (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

void *
nlm4_granted_msg_4_svc(nlm4_testargs *arg, struct svc_req *rqstp)
{
	static nlm4_res res;

	if (debug_level)
		log_from_addr("nlm4_granted_msg", rqstp);

	res.cookie = arg->cookie;
	res.stat.stat = lock_answer(arg->alock.svid, &arg->cookie,
		nlm4_granted, NULL, NLM_VERS4) == 0 ?
		nlm4_granted : nlm4_denied;
	transmit4_result(NLM4_GRANTED_RES, &res, getrpcaddr(rqstp));
	return (NULL);
}