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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_retstack {size_t top; size_t bottom; int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 size_t pt_retstack_size ; 
 int pte_invalid ; 

int pt_retstack_push(struct pt_retstack *retstack, uint64_t ip)
{
	uint8_t top, bottom;

	if (!retstack)
		return -pte_invalid;

	top = retstack->top;
	bottom = retstack->bottom;

	retstack->stack[top] = ip;

	top = (top == pt_retstack_size ? 0 : top + 1);

	if (bottom == top)
		bottom = (bottom == pt_retstack_size ? 0 : bottom + 1);

	retstack->top = top;
	retstack->bottom = bottom;

	return 0;
}