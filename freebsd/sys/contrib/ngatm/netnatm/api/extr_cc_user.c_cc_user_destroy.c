#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccuser {struct ccuser* sap; int /*<<< orphan*/  name; TYPE_1__* cc; } ;
struct TYPE_2__ {int log; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCFREE (struct ccuser*) ; 
 int CCLOG_USER_INST ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ccuser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_abort (struct ccuser*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_user_log (struct ccuser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_sig_flush (struct ccuser*) ; 
 int /*<<< orphan*/  node_link ; 

void
cc_user_destroy(struct ccuser *user)
{

	if (user->cc->log & CCLOG_USER_INST)
		cc_user_log(user, "destroy '%s'", user->name);

	cc_user_abort(user, NULL);

	if (user->sap != NULL)
		CCFREE(user->sap);

	cc_user_sig_flush(user);

	LIST_REMOVE(user, node_link);
	CCFREE(user);
}