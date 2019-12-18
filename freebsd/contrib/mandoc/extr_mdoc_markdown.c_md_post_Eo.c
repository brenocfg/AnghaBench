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
struct roff_node {scalar_t__ end; TYPE_2__* parent; int /*<<< orphan*/ * child; } ;
struct TYPE_6__ {int /*<<< orphan*/ * child; } ;
struct TYPE_5__ {TYPE_3__* tail; TYPE_1__* head; } ;
struct TYPE_4__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 scalar_t__ ENDBODY_NOT ; 
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_Eo(struct roff_node *n)
{
	if (n->end != ENDBODY_NOT) {
		outflags |= MD_spc;
		return;
	}

	if (n->child == NULL && n->parent->head->child == NULL)
		return;

	if (n->parent->tail != NULL && n->parent->tail->child != NULL)
		outflags &= ~MD_spc;
        else
		outflags |= MD_spc;
}