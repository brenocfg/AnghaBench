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
struct roff_node {scalar_t__ tok; TYPE_2__* next; TYPE_3__* prev; TYPE_1__* parent; } ;
struct TYPE_6__ {scalar_t__ tok; } ;
struct TYPE_5__ {scalar_t__ tok; } ;
struct TYPE_4__ {scalar_t__ tok; } ;

/* Variables and functions */
 scalar_t__ MDOC_Rs ; 
 int /*<<< orphan*/  MD_nl ; 
 int /*<<< orphan*/  md_post_raw (struct roff_node*) ; 
 int /*<<< orphan*/  md_word (char*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_pc(struct roff_node *n)
{
	md_post_raw(n);
	if (n->parent->tok != MDOC_Rs)
		return;
	if (n->next != NULL) {
		md_word(",");
		if (n->prev != NULL &&
		    n->prev->tok == n->tok &&
		    n->next->tok == n->tok)
			md_word("and");
	} else {
		md_word(".");
		outflags |= MD_nl;
	}
}