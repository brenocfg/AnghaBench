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
struct option {size_t val; int /*<<< orphan*/ * flag; int /*<<< orphan*/  has_arg; int /*<<< orphan*/  name; } ;
struct ibdiag_opt {size_t letter; int /*<<< orphan*/  has_arg; int /*<<< orphan*/  name; } ;

/* Variables and functions */

__attribute__((used)) static void make_opt(struct option *l, const struct ibdiag_opt *o,
		     const struct ibdiag_opt *map[])
{
	l->name = o->name;
	l->has_arg = o->has_arg;
	l->flag = NULL;
	l->val = o->letter;
	if (!map[l->val])
		map[l->val] = o;
}