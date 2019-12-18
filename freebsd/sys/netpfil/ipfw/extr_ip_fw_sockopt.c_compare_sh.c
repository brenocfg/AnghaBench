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
struct ipfw_sopt_handler {scalar_t__ opcode; scalar_t__ version; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_sh(const void *_a, const void *_b)
{
	const struct ipfw_sopt_handler *a, *b;

	a = (const struct ipfw_sopt_handler *)_a;
	b = (const struct ipfw_sopt_handler *)_b;

	if (a->opcode < b->opcode)
		return (-1);
	else if (a->opcode > b->opcode)
		return (1);

	if (a->version < b->version)
		return (-1);
	else if (a->version > b->version)
		return (1);

	/* bsearch helper */
	if (a->handler == NULL)
		return (0);

	if ((uintptr_t)a->handler < (uintptr_t)b->handler)
		return (-1);
	else if ((uintptr_t)a->handler > (uintptr_t)b->handler)
		return (1);

	return (0);
}