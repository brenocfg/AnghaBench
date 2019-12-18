#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roff_node {TYPE_3__* norm; } ;
struct TYPE_6__ {TYPE_2__* Es; } ;
struct TYPE_5__ {TYPE_1__* child; } ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  md_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_En(struct roff_node *n)
{
	if (n->norm->Es == NULL ||
	    n->norm->Es->child == NULL)
		return 1;

	md_word(n->norm->Es->child->string);
	outflags &= ~MD_spc;
	return 1;
}