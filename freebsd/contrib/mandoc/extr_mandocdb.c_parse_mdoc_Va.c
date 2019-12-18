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
struct roff_node {scalar_t__ type; scalar_t__ tok; TYPE_1__* child; } ;
struct roff_meta {int dummy; } ;
struct mpage {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 scalar_t__ MDOC_Va ; 
 scalar_t__ ROFFT_BODY ; 
 scalar_t__ ROFFT_ELEM ; 
 scalar_t__ ROFFT_TEXT ; 
 int TYPE_Va ; 
 int TYPE_Vt ; 
 int /*<<< orphan*/  deroff (char**,struct roff_node const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  putkey (struct mpage*,char*,int) ; 

__attribute__((used)) static int
parse_mdoc_Va(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{
	char *cp;

	if (n->type != ROFFT_ELEM && n->type != ROFFT_BODY)
		return 0;

	if (n->child != NULL &&
	    n->child->next == NULL &&
	    n->child->type == ROFFT_TEXT)
		return 1;

	cp = NULL;
	deroff(&cp, n);
	if (cp != NULL) {
		putkey(mpage, cp, TYPE_Vt | (n->tok == MDOC_Va ||
		    n->type == ROFFT_BODY ? TYPE_Va : 0));
		free(cp);
	}

	return 0;
}