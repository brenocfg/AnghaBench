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
struct cidr {struct cidr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cidr*) ; 
 struct cidr* stack ; 

__attribute__((used)) static bool cidr_pop(struct cidr *a)
{
	struct cidr *old = stack;

	if (old)
	{
		stack = stack->next;
		free(old);

		return true;
	}

	return false;
}