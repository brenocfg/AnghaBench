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
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 scalar_t__ acct_configured ; 
 int /*<<< orphan*/ * acct_cred ; 
 scalar_t__ acct_flags ; 
 int /*<<< orphan*/  acct_limit ; 
 int /*<<< orphan*/  acct_sx ; 
 int /*<<< orphan*/ * acct_vp ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lim_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vn_close (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,struct thread*) ; 

__attribute__((used)) static int
acct_disable(struct thread *td, int logging)
{
	int error;

	sx_assert(&acct_sx, SX_XLOCKED);
	error = vn_close(acct_vp, acct_flags, acct_cred, td);
	crfree(acct_cred);
	lim_free(acct_limit);
	acct_configured = 0;
	acct_vp = NULL;
	acct_cred = NULL;
	acct_flags = 0;
	if (logging)
		log(LOG_NOTICE, "Accounting disabled\n");
	return (error);
}