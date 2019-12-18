#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct roff_node {TYPE_5__* parent; TYPE_2__* prev; TYPE_1__* child; } ;
struct TYPE_10__ {scalar_t__ tok; TYPE_4__* parent; } ;
struct TYPE_9__ {TYPE_3__* parent; int /*<<< orphan*/ * prev; } ;
struct TYPE_8__ {scalar_t__ tok; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  string; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ MDOC_It ; 
 scalar_t__ MDOC_Xo ; 
 scalar_t__ ROFFT_TEXT ; 
 char* html_make_id (struct roff_node const*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
cond_id(const struct roff_node *n)
{
	if (n->child != NULL &&
	    n->child->type == ROFFT_TEXT &&
	    (n->prev == NULL ||
	     (n->prev->type == ROFFT_TEXT &&
	      strcmp(n->prev->string, "|") == 0)) &&
	    (n->parent->tok == MDOC_It ||
	     (n->parent->tok == MDOC_Xo &&
	      n->parent->parent->prev == NULL &&
	      n->parent->parent->parent->tok == MDOC_It)))
		return html_make_id(n, 1);
	return NULL;
}