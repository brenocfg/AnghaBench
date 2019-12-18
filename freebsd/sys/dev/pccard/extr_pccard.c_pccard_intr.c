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
struct pccard_function {int /*<<< orphan*/  intr_handler_arg; int /*<<< orphan*/  (* intr_handler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pccard_intr(void *arg)
{
	struct pccard_function *pf = (struct pccard_function*) arg;
	
	pf->intr_handler(pf->intr_handler_arg);	
}