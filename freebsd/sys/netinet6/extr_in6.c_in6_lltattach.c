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
struct lltable {int /*<<< orphan*/  llt_mark_used; int /*<<< orphan*/  llt_match_prefix; int /*<<< orphan*/  llt_free_entry; int /*<<< orphan*/  llt_fill_sa_entry; int /*<<< orphan*/  llt_hash; int /*<<< orphan*/  llt_dump_entry; int /*<<< orphan*/  llt_delete_entry; int /*<<< orphan*/  llt_alloc_entry; int /*<<< orphan*/  llt_lookup; struct ifnet* llt_ifp; int /*<<< orphan*/  llt_af; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_LLTBL_DEFAULT_HSIZE ; 
 int /*<<< orphan*/  in6_lltable_alloc ; 
 int /*<<< orphan*/  in6_lltable_delete_entry ; 
 int /*<<< orphan*/  in6_lltable_dump_entry ; 
 int /*<<< orphan*/  in6_lltable_fill_sa_entry ; 
 int /*<<< orphan*/  in6_lltable_free_entry ; 
 int /*<<< orphan*/  in6_lltable_hash ; 
 int /*<<< orphan*/  in6_lltable_lookup ; 
 int /*<<< orphan*/  in6_lltable_mark_used ; 
 int /*<<< orphan*/  in6_lltable_match_prefix ; 
 struct lltable* lltable_allocate_htbl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lltable_link (struct lltable*) ; 

__attribute__((used)) static struct lltable *
in6_lltattach(struct ifnet *ifp)
{
	struct lltable *llt;

	llt = lltable_allocate_htbl(IN6_LLTBL_DEFAULT_HSIZE);
	llt->llt_af = AF_INET6;
	llt->llt_ifp = ifp;

	llt->llt_lookup = in6_lltable_lookup;
	llt->llt_alloc_entry = in6_lltable_alloc;
	llt->llt_delete_entry = in6_lltable_delete_entry;
	llt->llt_dump_entry = in6_lltable_dump_entry;
	llt->llt_hash = in6_lltable_hash;
	llt->llt_fill_sa_entry = in6_lltable_fill_sa_entry;
	llt->llt_free_entry = in6_lltable_free_entry;
	llt->llt_match_prefix = in6_lltable_match_prefix;
	llt->llt_mark_used = in6_lltable_mark_used;
 	lltable_link(llt);

	return (llt);
}