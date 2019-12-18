#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct nlm_holder {int dummy; } ;
struct nlm4_lock {int dummy; } ;
struct nlm4_holder {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; } ;
struct TYPE_12__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; } ;
struct TYPE_8__ {TYPE_7__ holder; } ;
struct TYPE_9__ {TYPE_1__ nlm_testrply_u; int /*<<< orphan*/  stat; } ;
struct TYPE_10__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm_testres ;
struct TYPE_11__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  alock; } ;
typedef  TYPE_4__ nlm_testargs ;

/* Variables and functions */
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,struct nlm4_holder*,int) ; 
 int /*<<< orphan*/  nlm_denied ; 
 int /*<<< orphan*/  nlm_granted ; 
 int /*<<< orphan*/  nlmtonlm4 (int /*<<< orphan*/ *,struct nlm4_lock*) ; 
 struct nlm4_holder* testlock (struct nlm4_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

nlm_testres *
nlm_test_1_svc(nlm_testargs *arg, struct svc_req *rqstp)
{
	static nlm_testres res;
	struct nlm4_lock arg4;
	struct nlm4_holder *holder;
	nlmtonlm4(&arg->alock, &arg4);

	if (debug_level)
		log_from_addr("nlm_test", rqstp);

	holder = testlock(&arg4, arg->exclusive, 0);
	/*
	 * Copy the cookie from the argument into the result.  Note that this
	 * is slightly hazardous, as the structure contains a pointer to a
	 * malloc()ed buffer that will get freed by the caller.  However, the
	 * main function transmits the result before freeing the argument
	 * so it is in fact safe.
	 */
	res.cookie = arg->cookie;
	if (holder == NULL) {
		res.stat.stat = nlm_granted;
	} else {
		res.stat.stat = nlm_denied;
		memcpy(&res.stat.nlm_testrply_u.holder, holder,
		    sizeof(struct nlm_holder));
		res.stat.nlm_testrply_u.holder.l_offset = holder->l_offset;
		res.stat.nlm_testrply_u.holder.l_len = holder->l_len;
	}
	return (&res);
}