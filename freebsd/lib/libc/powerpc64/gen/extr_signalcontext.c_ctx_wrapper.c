#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * uc_link; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  (* handler_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcontext (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctx_wrapper(ucontext_t *ucp, handler_t func, uint32_t sig, uint32_t sig_si,
	    uint32_t sig_uc)
{

	(*func)(sig, sig_si, sig_uc);
	if (ucp->uc_link == NULL)
		exit(0);
	setcontext((const ucontext_t *)ucp->uc_link);
	/* should never get here */
	abort();
	/* NOTREACHED */
}