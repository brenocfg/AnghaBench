#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct roff_node {TYPE_4__* norm; } ;
struct TYPE_8__ {TYPE_3__* Es; } ;
struct TYPE_7__ {TYPE_2__* child; } ;
struct TYPE_6__ {TYPE_1__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  md_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_En(struct roff_node *n)
{
	if (n->norm->Es == NULL ||
	    n->norm->Es->child == NULL ||
	    n->norm->Es->child->next == NULL)
		return;

	outflags &= ~MD_spc;
	md_word(n->norm->Es->child->next->string);
}