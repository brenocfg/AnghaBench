#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_probe_t ;
struct TYPE_10__ {int /*<<< orphan*/  dthb_len; int /*<<< orphan*/ * dthb_chain; struct TYPE_10__* dthb_next; } ;
typedef  TYPE_1__ dtrace_hashbucket_t ;
struct TYPE_11__ {int dth_mask; int dth_nbuckets; int dth_size; TYPE_1__** dth_tab; } ;
typedef  TYPE_2__ dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_HASHEQ (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** DTRACE_HASHNEXT (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** DTRACE_HASHPREV (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int DTRACE_HASHSTR (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  dtrace_hash_resize (TYPE_2__*) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_hash_add(dtrace_hash_t *hash, dtrace_probe_t *new)
{
	int hashval = DTRACE_HASHSTR(hash, new);
	int ndx = hashval & hash->dth_mask;
	dtrace_hashbucket_t *bucket = hash->dth_tab[ndx];
	dtrace_probe_t **nextp, **prevp;

	for (; bucket != NULL; bucket = bucket->dthb_next) {
		if (DTRACE_HASHEQ(hash, bucket->dthb_chain, new))
			goto add;
	}

	if ((hash->dth_nbuckets >> 1) > hash->dth_size) {
		dtrace_hash_resize(hash);
		dtrace_hash_add(hash, new);
		return;
	}

	bucket = kmem_zalloc(sizeof (dtrace_hashbucket_t), KM_SLEEP);
	bucket->dthb_next = hash->dth_tab[ndx];
	hash->dth_tab[ndx] = bucket;
	hash->dth_nbuckets++;

add:
	nextp = DTRACE_HASHNEXT(hash, new);
	ASSERT(*nextp == NULL && *(DTRACE_HASHPREV(hash, new)) == NULL);
	*nextp = bucket->dthb_chain;

	if (bucket->dthb_chain != NULL) {
		prevp = DTRACE_HASHPREV(hash, bucket->dthb_chain);
		ASSERT(*prevp == NULL);
		*prevp = new;
	}

	bucket->dthb_chain = new;
	bucket->dthb_len++;
}