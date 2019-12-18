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
struct opcode_obj_rewrite {scalar_t__ opcode; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_opcodes(const void *_a, const void *_b)
{
	const struct opcode_obj_rewrite *a, *b;

	a = (const struct opcode_obj_rewrite *)_a;
	b = (const struct opcode_obj_rewrite *)_b;

	if (a->opcode < b->opcode)
		return (-1);
	else if (a->opcode > b->opcode)
		return (1);

	return (0);
}