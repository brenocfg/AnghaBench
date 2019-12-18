#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  n_flags; struct TYPE_3__* n_next; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 int /*<<< orphan*/  NF_NODEST ; 
 TYPE_1__* graph ; 

__attribute__((used)) static void
clear_cycle(void)
{
	NODE *n;

	for (n = graph; n != NULL; n = n->n_next)
		n->n_flags &= ~NF_NODEST;
}