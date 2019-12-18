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
struct roff_node {TYPE_1__* args; } ;
struct roff_man {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * argv; scalar_t__ argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  check_argv (struct roff_man*,struct roff_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_args(struct roff_man *mdoc, struct roff_node *n)
{
	int		 i;

	if (NULL == n->args)
		return;

	assert(n->args->argc);
	for (i = 0; i < (int)n->args->argc; i++)
		check_argv(mdoc, n, &n->args->argv[i]);
}