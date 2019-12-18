#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_probe_t ;
struct TYPE_7__ {struct TYPE_7__* dthb_next; int /*<<< orphan*/ * dthb_chain; } ;
typedef  TYPE_1__ dtrace_hashbucket_t ;
struct TYPE_8__ {int dth_size; int dth_mask; TYPE_1__** dth_tab; } ;
typedef  TYPE_2__ dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACE_HASHSTR (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,int) ; 
 TYPE_1__** kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_hash_resize(dtrace_hash_t *hash)
{
	int size = hash->dth_size, i, ndx;
	int new_size = hash->dth_size << 1;
	int new_mask = new_size - 1;
	dtrace_hashbucket_t **new_tab, *bucket, *next;

	ASSERT((new_size & new_mask) == 0);

	new_tab = kmem_zalloc(new_size * sizeof (void *), KM_SLEEP);

	for (i = 0; i < size; i++) {
		for (bucket = hash->dth_tab[i]; bucket != NULL; bucket = next) {
			dtrace_probe_t *probe = bucket->dthb_chain;

			ASSERT(probe != NULL);
			ndx = DTRACE_HASHSTR(hash, probe) & new_mask;

			next = bucket->dthb_next;
			bucket->dthb_next = new_tab[ndx];
			new_tab[ndx] = bucket;
		}
	}

	kmem_free(hash->dth_tab, hash->dth_size * sizeof (void *));
	hash->dth_tab = new_tab;
	hash->dth_size = new_size;
	hash->dth_mask = new_mask;
}