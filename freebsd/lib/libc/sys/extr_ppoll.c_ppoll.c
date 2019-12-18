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
struct timespec {int dummy; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 size_t INTERPOS_ppoll ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (struct pollfd*,int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/  const*) ; 

int
ppoll(struct pollfd pfd[], nfds_t nfds, const struct timespec *__restrict
    timeout, const sigset_t *__restrict newsigmask)
{

	return (((int (*)(struct pollfd *, nfds_t, const struct timespec *,
	    const sigset_t *)) __libc_interposing[INTERPOS_ppoll])(pfd, nfds,
	    timeout, newsigmask));
}