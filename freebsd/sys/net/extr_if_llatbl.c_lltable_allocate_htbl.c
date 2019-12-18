#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct lltable {int llt_hsize; int /*<<< orphan*/  llt_free_tbl; int /*<<< orphan*/  llt_foreach_entry; int /*<<< orphan*/  llt_prefix_free; int /*<<< orphan*/  llt_unlink_entry; int /*<<< orphan*/  llt_link_entry; int /*<<< orphan*/ * lle_head; } ;
struct llentries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_LLTABLE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  htable_foreach_lle ; 
 int /*<<< orphan*/  htable_free_tbl ; 
 int /*<<< orphan*/  htable_link_entry ; 
 int /*<<< orphan*/  htable_prefix_free ; 
 int /*<<< orphan*/  htable_unlink_entry ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

struct lltable *
lltable_allocate_htbl(uint32_t hsize)
{
	struct lltable *llt;
	int i;

	llt = malloc(sizeof(struct lltable), M_LLTABLE, M_WAITOK | M_ZERO);
	llt->llt_hsize = hsize;
	llt->lle_head = malloc(sizeof(struct llentries) * hsize,
	    M_LLTABLE, M_WAITOK | M_ZERO);

	for (i = 0; i < llt->llt_hsize; i++)
		CK_LIST_INIT(&llt->lle_head[i]);

	/* Set some default callbacks */
	llt->llt_link_entry = htable_link_entry;
	llt->llt_unlink_entry = htable_unlink_entry;
	llt->llt_prefix_free = htable_prefix_free;
	llt->llt_foreach_entry = htable_foreach_lle;
	llt->llt_free_tbl = htable_free_tbl;

	return (llt);
}