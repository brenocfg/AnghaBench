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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t INTERPOS_sigwaitinfo ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
sigwaitinfo(const sigset_t * __restrict set, siginfo_t * __restrict info)
{

	return (((int (*)(const sigset_t *, siginfo_t *))
	    __libc_interposing[INTERPOS_sigwaitinfo])(set, info));
}