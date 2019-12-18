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
struct ccuser {int state; TYPE_1__* cc; } ;
typedef  enum user_state { ____Placeholder_user_state } user_state ;
struct TYPE_2__ {int log; } ;

/* Variables and functions */
 int CCLOG_USER_STATE ; 
 int /*<<< orphan*/  cc_user_log (struct ccuser*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stab ; 

__attribute__((used)) static __inline void
set_state(struct ccuser *user, enum user_state ns)
{
	if (user->state != ns) {
		if (user->cc->log & CCLOG_USER_STATE)
			cc_user_log(user, "%s -> %s",
			    stab[user->state], stab[ns]);
		user->state = ns;
	}
}