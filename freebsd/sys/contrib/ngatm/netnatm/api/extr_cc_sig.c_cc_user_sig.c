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
typedef  int /*<<< orphan*/  u_int ;
struct ccuser {TYPE_1__* cc; } ;
struct ccsig {int dummy; } ;
typedef  enum user_sig { ____Placeholder_user_sig } user_sig ;
struct TYPE_3__ {int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SIG_USER ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_sig_log (TYPE_1__*,char*,int /*<<< orphan*/ ,struct ccuser*) ; 
 int /*<<< orphan*/ * cc_user_sigtab ; 
 int /*<<< orphan*/  link ; 
 struct ccsig* sig_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct ccuser*,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 

int
cc_user_sig(struct ccuser *user, enum user_sig sig, void *arg1, u_int arg2)
{
	struct ccsig *s;

	s = sig_alloc(user->cc, SIG_USER, user, 0, sig, arg1, arg2);
	if (s == NULL)
		return (ENOMEM);
	TAILQ_INSERT_TAIL(&user->cc->sigs, s, link);
	cc_sig_log(user->cc, "queuing sig %s to user %p", cc_user_sigtab[sig],
	    user);
	return (0);
}