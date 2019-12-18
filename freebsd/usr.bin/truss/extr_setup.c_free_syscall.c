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
typedef  size_t u_int ;
struct TYPE_2__ {size_t nargs; int /*<<< orphan*/ * s_args; } ;
struct threadinfo {scalar_t__ in_syscall; TYPE_1__ cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
free_syscall(struct threadinfo *t)
{
	u_int i;

	for (i = 0; i < t->cs.nargs; i++)
		free(t->cs.s_args[i]);
	memset(&t->cs, 0, sizeof(t->cs));
	t->in_syscall = 0;
}