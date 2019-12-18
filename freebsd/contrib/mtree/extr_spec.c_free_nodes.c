#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* tags; struct TYPE_4__* sha512digest; struct TYPE_4__* sha384digest; struct TYPE_4__* sha256digest; struct TYPE_4__* sha1digest; struct TYPE_4__* rmd160digest; struct TYPE_4__* md5digest; struct TYPE_4__* slink; struct TYPE_4__* child; struct TYPE_4__* next; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 int /*<<< orphan*/  REPLACEPTR (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
free_nodes(NODE *root)
{
	NODE	*cur, *next;

	if (root == NULL)
		return;

	next = NULL;
	for (cur = root; cur != NULL; cur = next) {
		next = cur->next;
		free_nodes(cur->child);
		REPLACEPTR(cur->slink, NULL);
		REPLACEPTR(cur->md5digest, NULL);
		REPLACEPTR(cur->rmd160digest, NULL);
		REPLACEPTR(cur->sha1digest, NULL);
		REPLACEPTR(cur->sha256digest, NULL);
		REPLACEPTR(cur->sha384digest, NULL);
		REPLACEPTR(cur->sha512digest, NULL);
		REPLACEPTR(cur->tags, NULL);
		REPLACEPTR(cur, NULL);
	}
}