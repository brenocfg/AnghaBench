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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 size_t INTERPOS_pselect ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int /*<<< orphan*/  const*) ; 

int
pselect(int n, fd_set *rs, fd_set *ws, fd_set *es, const struct timespec *t,
    const sigset_t *s)
{

	return (((int (*)(int, fd_set *, fd_set *, fd_set *,
	    const struct timespec *, const sigset_t *))
	    __libc_interposing[INTERPOS_pselect])(n, rs, ws, es, t, s));
}