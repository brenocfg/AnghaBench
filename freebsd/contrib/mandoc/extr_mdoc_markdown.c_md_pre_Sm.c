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
struct roff_node {TYPE_1__* child; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int MD_Sm ; 
 int MD_spc ; 
 int outflags ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
md_pre_Sm(struct roff_node *n)
{
	if (n->child == NULL)
		outflags ^= MD_Sm;
	else if (strcmp("on", n->child->string) == 0)
		outflags |= MD_Sm;
	else
		outflags &= ~MD_Sm;

	if (outflags & MD_Sm)
		outflags |= MD_spc;

	return 0;
}