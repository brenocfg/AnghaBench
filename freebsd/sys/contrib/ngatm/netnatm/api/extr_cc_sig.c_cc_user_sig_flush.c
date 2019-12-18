#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ccuser {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_USER ; 
 int /*<<< orphan*/  cc_sig_log (int /*<<< orphan*/ ,char*,struct ccuser*) ; 
 int /*<<< orphan*/  sig_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ccuser*) ; 

void
cc_user_sig_flush(struct ccuser *user)
{

	cc_sig_log(user->cc, "flushing signals to user %p", user);
	sig_flush(user->cc, SIG_USER, user);
}