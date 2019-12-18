#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct process {TYPE_1__* p_cwd; struct process* p_command; } ;
struct TYPE_2__ {scalar_t__ di_count; scalar_t__ di_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfree (TYPE_1__*) ; 
 int /*<<< orphan*/  xfree (struct process*) ; 

__attribute__((used)) static void
pfree(struct process *pp)
{	
    xfree(pp->p_command);
    if (pp->p_cwd && --pp->p_cwd->di_count == 0)
	if (pp->p_cwd->di_next == 0)
	    dfree(pp->p_cwd);
    xfree(pp);
}