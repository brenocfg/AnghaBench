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
struct termp {int dummy; } ;
struct roff_node {int /*<<< orphan*/ * prev; TYPE_1__* parent; TYPE_2__* body; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_3__* child; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ tok; } ;

/* Variables and functions */
 scalar_t__ MAN_RS ; 
 scalar_t__ ROFFT_ROOT ; 
 scalar_t__ ROFFT_TBL ; 
 int /*<<< orphan*/  term_newln (struct termp*) ; 
 int /*<<< orphan*/  term_vspace (struct termp*) ; 

__attribute__((used)) static void
print_bvspace(struct termp *p, const struct roff_node *n, int pardist)
{
	int	 i;

	term_newln(p);

	if (n->body != NULL && n->body->child != NULL)
		if (n->body->child->type == ROFFT_TBL)
			return;

	if (n->parent->type == ROFFT_ROOT || n->parent->tok != MAN_RS)
		if (n->prev == NULL)
			return;

	for (i = 0; i < pardist; i++)
		term_vspace(p);
}