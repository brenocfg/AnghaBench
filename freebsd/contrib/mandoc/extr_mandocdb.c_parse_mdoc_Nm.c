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
struct roff_node {scalar_t__ sec; scalar_t__ type; TYPE_1__* child; } ;
struct roff_meta {int /*<<< orphan*/  title; int /*<<< orphan*/ * name; } ;
struct mpage {int name_head_done; } ;
struct TYPE_2__ {int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_HEAD ; 
 int /*<<< orphan*/  NAME_SYN ; 
 int /*<<< orphan*/  NAME_TITLE ; 
 scalar_t__ ROFFT_HEAD ; 
 scalar_t__ SEC_NAME ; 
 scalar_t__ SEC_SYNOPSIS ; 
 int /*<<< orphan*/  putkey (struct mpage*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putmdockey (struct mpage*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_mdoc_Nm(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{

	if (SEC_NAME == n->sec)
		putmdockey(mpage, n->child, NAME_TITLE, 0);
	else if (n->sec == SEC_SYNOPSIS && n->type == ROFFT_HEAD) {
		if (n->child == NULL)
			putkey(mpage, meta->name, NAME_SYN);
		else
			putmdockey(mpage, n->child, NAME_SYN, 0);
	}
	if ( ! (mpage->name_head_done ||
	    n->child == NULL || n->child->string == NULL ||
	    strcasecmp(n->child->string, meta->title))) {
		putkey(mpage, n->child->string, NAME_HEAD);
		mpage->name_head_done = 1;
	}
	return 0;
}