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
struct TYPE_4__ {int /*<<< orphan*/ * uc_link; } ;
typedef  TYPE_1__ ucontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcontext (TYPE_1__ const*) ; 

void
ctx_done(ucontext_t *ucp)
{       
	        
	if (ucp->uc_link == NULL) {
		exit(0);
	} else {  
		setcontext((const ucontext_t *)ucp->uc_link);
		abort();
	}                                                      
}