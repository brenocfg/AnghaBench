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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpath1 ; 
 scalar_t__ fpath1_initialized ; 
 int /*<<< orphan*/  fpath2 ; 
 scalar_t__ fpath2_initialized ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
priv_acct_cleanup(int asroot, int injail, struct test *test)
{

	(void)acct(NULL);
	if (fpath1_initialized) {
		(void)unlink(fpath1);
		fpath1_initialized = 0;
	}
	if (fpath2_initialized) {
		(void)unlink(fpath2);
		fpath2_initialized = 0;
	}
}