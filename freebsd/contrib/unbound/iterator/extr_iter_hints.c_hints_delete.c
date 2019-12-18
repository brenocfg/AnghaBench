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
struct iter_hints {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct iter_hints*) ; 
 int /*<<< orphan*/  hints_del_tree (struct iter_hints*) ; 

void 
hints_delete(struct iter_hints* hints)
{
	if(!hints) 
		return;
	hints_del_tree(hints);
	free(hints);
}