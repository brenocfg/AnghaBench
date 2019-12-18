#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mc_len; } ;
struct TYPE_6__ {int /*<<< orphan*/ * uc_link; TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcontext (TYPE_2__ const*) ; 

void
_ctx_done(ucontext_t *ucp)
{
	if (ucp->uc_link == NULL)
		exit(0);
	else {
		/* invalidate context */
		ucp->uc_mcontext.mc_len = 0;

		setcontext((const ucontext_t *)ucp->uc_link);

		abort(); /* should never return from above call */
	}
}