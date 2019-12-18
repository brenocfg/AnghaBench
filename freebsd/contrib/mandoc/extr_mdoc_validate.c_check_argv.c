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
struct roff_node {int dummy; } ;
struct roff_man {int dummy; } ;
struct mdoc_argv {int /*<<< orphan*/ * value; int /*<<< orphan*/  pos; int /*<<< orphan*/  line; scalar_t__ sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_text (struct roff_man*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_argv(struct roff_man *mdoc, struct roff_node *n, struct mdoc_argv *v)
{
	int		 i;

	for (i = 0; i < (int)v->sz; i++)
		check_text(mdoc, v->line, v->pos, v->value[i]);
}