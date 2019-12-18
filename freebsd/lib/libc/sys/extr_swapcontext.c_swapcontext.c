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
typedef  int /*<<< orphan*/  ucontext_t ;

/* Variables and functions */
 size_t INTERPOS_swapcontext ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int
swapcontext(ucontext_t *oucp, const ucontext_t *ucp)
{

	return (((int (*)(ucontext_t *, const ucontext_t *))
	    __libc_interposing[INTERPOS_swapcontext])(oucp, ucp));
}