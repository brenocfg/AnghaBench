#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct roff_node {TYPE_2__* norm; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ Bl; } ;

/* Variables and functions */
 scalar_t__ LIST_column ; 
 int /*<<< orphan*/  MD_sp ; 
 int /*<<< orphan*/  md_post_D1 (struct roff_node*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_Bl(struct roff_node *n)
{
	n->norm->Bl.count = 0;
	if (n->norm->Bl.type == LIST_column)
		md_post_D1(n);
	outflags |= MD_sp;
}