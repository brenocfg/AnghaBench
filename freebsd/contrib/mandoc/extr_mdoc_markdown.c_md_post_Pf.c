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
struct roff_node {TYPE_1__* next; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int NODE_LINE ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_Pf(struct roff_node *n)
{
	if (n->next != NULL && (n->next->flags & NODE_LINE) == 0)
		outflags &= ~MD_spc;
}