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
typedef  TYPE_1__* uma_slab_t ;
typedef  size_t u_int ;
struct uma_hash {scalar_t__ uh_hashsize; int /*<<< orphan*/ * uh_slab_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  us_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t UMA_HASH (struct uma_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  us_hlink ; 

__attribute__((used)) static int
hash_expand(struct uma_hash *oldhash, struct uma_hash *newhash)
{
	uma_slab_t slab;
	u_int hval;
	u_int idx;

	if (!newhash->uh_slab_hash)
		return (0);

	if (oldhash->uh_hashsize >= newhash->uh_hashsize)
		return (0);

	/*
	 * I need to investigate hash algorithms for resizing without a
	 * full rehash.
	 */

	for (idx = 0; idx < oldhash->uh_hashsize; idx++)
		while (!SLIST_EMPTY(&oldhash->uh_slab_hash[idx])) {
			slab = SLIST_FIRST(&oldhash->uh_slab_hash[idx]);
			SLIST_REMOVE_HEAD(&oldhash->uh_slab_hash[idx], us_hlink);
			hval = UMA_HASH(newhash, slab->us_data);
			SLIST_INSERT_HEAD(&newhash->uh_slab_hash[hval],
			    slab, us_hlink);
		}

	return (1);
}