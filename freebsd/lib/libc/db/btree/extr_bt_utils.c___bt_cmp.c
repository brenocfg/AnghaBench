#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int flags; int /*<<< orphan*/  ksize; void* bytes; } ;
struct TYPE_23__ {int flags; int /*<<< orphan*/  ksize; void* bytes; } ;
struct TYPE_18__ {void* data; int /*<<< orphan*/  size; } ;
struct TYPE_22__ {int (* bt_cmp ) (TYPE_4__ const*,TYPE_4__*) ;TYPE_1__ bt_rdata; } ;
struct TYPE_21__ {void* data; int /*<<< orphan*/  size; } ;
struct TYPE_20__ {int /*<<< orphan*/  index; TYPE_2__* page; } ;
struct TYPE_19__ {scalar_t__ prevpg; int flags; } ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ EPG ;
typedef  TYPE_4__ DBT ;
typedef  TYPE_5__ BTREE ;
typedef  TYPE_6__ BLEAF ;
typedef  TYPE_7__ BINTERNAL ;

/* Variables and functions */
 TYPE_7__* GETBINTERNAL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* GETBLEAF (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int P_BIGKEY ; 
 int P_BLEAF ; 
 scalar_t__ P_INVALID ; 
 int RET_ERROR ; 
 scalar_t__ __ovfl_get (TYPE_5__*,void*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__ const*,TYPE_4__*) ; 

int
__bt_cmp(BTREE *t, const DBT *k1, EPG *e)
{
	BINTERNAL *bi;
	BLEAF *bl;
	DBT k2;
	PAGE *h;
	void *bigkey;

	/*
	 * The left-most key on internal pages, at any level of the tree, is
	 * guaranteed by the following code to be less than any user key.
	 * This saves us from having to update the leftmost key on an internal
	 * page when the user inserts a new key in the tree smaller than
	 * anything we've yet seen.
	 */
	h = e->page;
	if (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & P_BLEAF))
		return (1);

	bigkey = NULL;
	if (h->flags & P_BLEAF) {
		bl = GETBLEAF(h, e->index);
		if (bl->flags & P_BIGKEY)
			bigkey = bl->bytes;
		else {
			k2.data = bl->bytes;
			k2.size = bl->ksize;
		}
	} else {
		bi = GETBINTERNAL(h, e->index);
		if (bi->flags & P_BIGKEY)
			bigkey = bi->bytes;
		else {
			k2.data = bi->bytes;
			k2.size = bi->ksize;
		}
	}

	if (bigkey) {
		if (__ovfl_get(t, bigkey,
		    &k2.size, &t->bt_rdata.data, &t->bt_rdata.size))
			return (RET_ERROR);
		k2.data = t->bt_rdata.data;
	}
	return ((*t->bt_cmp)(k1, &k2));
}