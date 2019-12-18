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
struct ccuser {scalar_t__ aborted; scalar_t__ queue_max; scalar_t__ queue_act; int /*<<< orphan*/  config; TYPE_1__* accepted; int /*<<< orphan*/ * sap; int /*<<< orphan*/  connq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * acceptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CCFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USER_NULL ; 
 int /*<<< orphan*/  USER_P2P ; 
 int /*<<< orphan*/  cc_user_sig_flush (struct ccuser*) ; 
 int /*<<< orphan*/  set_state (struct ccuser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cc_user_reset(struct ccuser *user)
{

	CCASSERT(TAILQ_EMPTY(&user->connq), ("connq not empty"));

	if (user->sap != NULL) {
		CCFREE(user->sap);
		user->sap = NULL;
	}

	if (user->accepted != NULL) {
		user->accepted->acceptor = NULL;
		user->accepted = NULL;
	}
	user->config = USER_P2P;
	user->queue_act = 0;
	user->queue_max = 0;
	user->aborted = 0;

	set_state(user, USER_NULL);

	cc_user_sig_flush(user);
}