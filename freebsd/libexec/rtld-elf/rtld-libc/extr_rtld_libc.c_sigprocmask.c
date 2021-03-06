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
 int __sys_sigprocmask (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
sigprocmask(int how, const sigset_t *set, sigset_t *oset)
{

	return (__sys_sigprocmask(how, set, oset));
}