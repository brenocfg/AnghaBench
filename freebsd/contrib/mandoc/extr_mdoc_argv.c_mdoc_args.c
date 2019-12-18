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
struct roff_node {scalar_t__ tok; TYPE_2__* norm; struct roff_node* parent; } ;
struct roff_man {struct roff_node* last; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
typedef  enum margserr { ____Placeholder_margserr } margserr ;
typedef  enum argsflag { ____Placeholder_argsflag } argsflag ;
struct TYPE_6__ {int flags; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ Bl; } ;

/* Variables and functions */
 int ARGSFL_NONE ; 
 int ARGSFL_TABSEP ; 
 scalar_t__ LIST_column ; 
 scalar_t__ MDOC_Bl ; 
 int MDOC_Dd ; 
 int MDOC_It ; 
 int TOKEN_NONE ; 
 int args (struct roff_man*,int,int*,char*,int,char**) ; 
 TYPE_3__* mdocargs ; 

enum margserr
mdoc_args(struct roff_man *mdoc, int line, int *pos,
	char *buf, enum roff_tok tok, char **v)
{
	struct roff_node *n;
	enum argsflag	  fl;

	fl = tok == TOKEN_NONE ? ARGSFL_NONE : mdocargs[tok - MDOC_Dd].flags;

	/*
	 * We know that we're in an `It', so it's reasonable to expect
	 * us to be sitting in a `Bl'.  Someday this may not be the case
	 * (if we allow random `It's sitting out there), so provide a
	 * safe fall-back into the default behaviour.
	 */

	if (tok == MDOC_It) {
		for (n = mdoc->last; n != NULL; n = n->parent) {
			if (n->tok != MDOC_Bl)
				continue;
			if (n->norm->Bl.type == LIST_column)
				fl = ARGSFL_TABSEP;
			break;
		}
	}

	return args(mdoc, line, pos, buf, fl, v);
}