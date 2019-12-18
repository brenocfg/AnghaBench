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
struct roff_node {scalar_t__ end; TYPE_4__* parent; TYPE_2__* child; } ;
struct TYPE_8__ {TYPE_3__* tail; TYPE_1__* head; } ;
struct TYPE_7__ {int /*<<< orphan*/ * child; } ;
struct TYPE_6__ {scalar_t__ end; } ;
struct TYPE_5__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 scalar_t__ ENDBODY_NOT ; 
 int MD_nl ; 
 int MD_spc ; 
 int /*<<< orphan*/  md_preword () ; 
 int outflags ; 

__attribute__((used)) static int
md_pre_Eo(struct roff_node *n)
{
	if (n->end == ENDBODY_NOT &&
	    n->parent->head->child == NULL &&
	    n->child != NULL &&
	    n->child->end != ENDBODY_NOT)
		md_preword();
	else if (n->end != ENDBODY_NOT ? n->child != NULL :
	    n->parent->head->child != NULL && (n->child != NULL ||
	    (n->parent->tail != NULL && n->parent->tail->child != NULL)))
		outflags &= ~(MD_spc | MD_nl);
	return 1;
}