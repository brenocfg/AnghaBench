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
struct pt_retstack {scalar_t__ top; scalar_t__ bottom; } ;

/* Variables and functions */
 int pte_invalid ; 

int pt_retstack_is_empty(const struct pt_retstack *retstack)
{
	if (!retstack)
		return -pte_invalid;

	return (retstack->top == retstack->bottom ? 1 : 0);
}