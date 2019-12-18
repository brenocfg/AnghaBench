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
struct roff_node {char* string; TYPE_1__* next; struct roff_node* child; } ;
struct roff_meta {int dummy; } ;
struct mpage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_Xr ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putkey (struct mpage*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_mdoc_Xr(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{
	char	*cp;

	if (NULL == (n = n->child))
		return 0;

	if (NULL == n->next) {
		putkey(mpage, n->string, TYPE_Xr);
		return 0;
	}

	mandoc_asprintf(&cp, "%s(%s)", n->string, n->next->string);
	putkey(mpage, cp, TYPE_Xr);
	free(cp);
	return 0;
}