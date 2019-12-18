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

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  _panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bset ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poll_unblocksig(void)
{
	if(sigprocmask(SIG_SETMASK, &bset, NULL))
		_panic("sigprocmask(SIG_SETMASK): %s", strerror(errno));
}