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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNAL ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  _panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bset ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poll_blocksig(void)
{
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGNAL);

	if(sigprocmask(SIG_BLOCK, &set, &bset))
		_panic("sigprocmask(SIG_BLOCK): %s", strerror(errno));
}